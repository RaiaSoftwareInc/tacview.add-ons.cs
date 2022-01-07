using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading;
using System.Windows;
using System.Windows.Forms;
using System.Xml.Linq;
using TacviewSDK;

namespace M2000D.carto
{
	using ObjectHandle = System.IntPtr;

	/// <summary>
	/// Logique d'interaction pour DownloadMaps.xaml
	/// </summary>
	public partial class DownloadMaps : Window
	{
		private MainMenu mainMenu;
		private Wrapper tacview;
		private Wrapper.TelemetryClass telemetry;
		private Wms wms;
		private Process process;

		public Action LoadMaps { get; }
		public DownloadMaps(Action loadMaps)
		{
			InitializeComponent();
			this.LoadMaps = loadMaps;
			comboboxResolution.Items.Add("10.0");
			comboboxResolution.Items.Add("5.0");
			comboboxResolution.Items.Add("2.0");
			comboboxResolution.Items.Add("1.0");
			comboboxResolution.Items.Add("0.5");
			comboboxResolution.Items.Add("0.2");
			comboboxResolution.Items.Add("0.1");
			comboboxResolution.SelectedItem = "1.0";
		}
		void OnLoad(object sender, RoutedEventArgs e)
		{
			ListboxMaps.Items.SortDescriptions.Add(new System.ComponentModel.SortDescription("", System.ComponentModel.ListSortDirection.Ascending));
			var nlBE = new System.Globalization.CultureInfo("us-US");
			nlBE.NumberFormat.CurrencyGroupSeparator = ".";
			System.Threading.Thread.CurrentThread.CurrentCulture = nlBE;

			if (this.mainMenu.selectedServer.Contains("EsiocServer"))
			{
				if (Tools.checkIfTcpPortAvailable2(8080) == -1)
				{
					if (!startEsiocServer())
					{
						closeWindows();
					}
				}
			}
		}

		private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
		{
			e.Cancel = true; // this will prevent to close
							 //this.Hide(); // it'll hide the window
							 // here now you can call any method
		}
		internal void setParent(MainMenu mainMenu)
		{
			this.mainMenu = mainMenu;
			this.tacview = this.mainMenu.tacview;
			this.telemetry = this.tacview.Telemetry;
			string urlOfSelectedServer = this.mainMenu.ogcServerList[this.mainMenu.selectedServer];
			this.wms = new Wms(tacview, urlOfSelectedServer, this);
		}
		private void Ok_Click(object sender, RoutedEventArgs e)
		{
			DownloadMap();
		}
		private void Cancel_Click(object sender, RoutedEventArgs e)
		{

			this.closeWindows();
		}
		void ClosingEvent(object sender, System.ComponentModel.CancelEventArgs e)
		{
			closeWindows();
		}
		public void closeWindows()
		{
			tacview.Log.Info("Reload Maps");
			LoadMaps();
			if (this.wms != null)
			{
				this.wms.StopDownloadService();
				wms = null;
			}

			stopEsiocServer();

			try
			{
				this.Close();
				this.Hide();
			}
			catch
			{

			}
		}
		private void getCoordinates(out double topLeftLatitude, out double topLeftLongitude, out double bottomRightLatitude, out double bottomRightLongitude)
		{
			int objectCount = telemetry.GetObjectCount();

			if (objectCount == 0)
			{
				tacview.Log.Info("No objects found - calculating coordinates from camera position");
				GetCoordinatesFromCamera(out topLeftLatitude, out topLeftLongitude, out bottomRightLatitude, out bottomRightLongitude);
			}
			else
			{
				tacview.Log.Info(objectCount + " objects found - calculating coordinates from object position");
				GetCoordinatesFromObjects(out topLeftLatitude, out topLeftLongitude, out bottomRightLatitude, out bottomRightLongitude);
			}

		}
		private void GetCoordinatesFromObjects(out double topLeftLatitude, out double topLeftLongitude, out double bottomRightLatitude, out double bottomRightLongitude)
		{
			List<double> latitude = new List<double>();
			List<double> longitude = new List<double>();

			int objectCount = this.telemetry.GetObjectCount();

			for (int objectIndex = 0; objectIndex < objectCount; objectIndex++)
			{
				ObjectHandle objectHandle = tacview.Telemetry.GetObjectHandleByIndex(objectIndex);
				TacviewSDK.Wrapper.ObjectTransformOutput transform;
				tacview.Telemetry.GetTransform(objectHandle, tacview.Context.GetAbsoluteTime(), out transform);
				latitude.Add(Tools.ConvertRadiansToDegrees(transform.latitude));
				longitude.Add(Tools.ConvertRadiansToDegrees(transform.longitude));
			}

			latitude.Sort();
			longitude.Sort();

			topLeftLatitude = Math.Ceiling(latitude.Max() + 1);
			bottomRightLatitude = Math.Floor(latitude.Min() - 1);

			if ((longitude.Max() - longitude.Min()) > 180)
			{
				topLeftLongitude = Math.Floor(longitude.Max() - 1);
				bottomRightLongitude = Math.Ceiling(longitude.Min() + 1);
			}
			else
			{
				topLeftLongitude = Math.Floor(longitude.Min() - 1);
				bottomRightLongitude = Math.Ceiling(longitude.Max() + 1);
			}
			tacview.Log.Info(string.Format("From object position, calculated square area from top left to bottom right: {0:0.00}, {1:0.00}, {2:0.00}, {3:0.00}",
				topLeftLatitude,
				topLeftLongitude,
				bottomRightLatitude,
				bottomRightLongitude));
		}
		private void DownloadMap()
		{
			double topLeftLatitude;
			double topLeftLongitude;
			double bottomRightLatitude;
			double bottomRightLongitude;

			getCoordinates(out topLeftLatitude, out topLeftLongitude, out bottomRightLatitude, out bottomRightLongitude);
			double resolution = 1;
			try
			{
				resolution = Convert.ToDouble(comboboxResolution.SelectedItem);
			}
			catch { }
			this.wms.DownloadService(ListboxMaps.SelectedItems, topLeftLatitude, topLeftLongitude, bottomRightLatitude, bottomRightLongitude, resolution);
		}
		private void GetCoordinatesFromCamera(out double topLeftLatitude, out double topLeftLongitude, out double bottomRightLatitude, out double bottomRightLongitude)
		{
			double lat = 0;
			double lon = 0;
			double alt = 0;
			tacview.Context.Camera.GetSphericalPosition(out lon, out lat, out alt);

			double latitude = Convert.ToDouble(lat);
			double longitude = Convert.ToDouble(lon);

			tacview.Log.Info(string.Format("From camera position, calculated center: {0:0.00}, {1:0.00}", Tools.ConvertRadiansToDegrees(latitude), Tools.ConvertRadiansToDegrees(longitude)));


			topLeftLatitude = Math.Ceiling(Tools.ConvertRadiansToDegrees(latitude) + 2);
			topLeftLongitude = Math.Floor(Tools.ConvertRadiansToDegrees(longitude) - 2);
			bottomRightLatitude = Math.Floor(Tools.ConvertRadiansToDegrees(latitude) - 2);
			bottomRightLongitude = Math.Ceiling(Tools.ConvertRadiansToDegrees(longitude) + 2);


			if (bottomRightLongitude > 180)
			{
				bottomRightLongitude = 360 - bottomRightLongitude;
			}
			if (topLeftLongitude < -180)
			{
				topLeftLongitude = 360 + topLeftLongitude;
			}

			tacview.Log.Info(string.Format("From camera position, calculated square area from top left to bottom right: {0:0.00}, {1:0.00}, {2:0.00}, {3:0.00}",
				topLeftLatitude,
				topLeftLongitude,
				bottomRightLatitude,
				bottomRightLongitude));
		}
		public bool startEsiocServer()
		{
			FolderBrowserDialog fbd = new FolderBrowserDialog();
			DialogResult result = fbd.ShowDialog();
			bool findNoResidentMission = false;
			bool findResidentMission = false;
			bool ret = true;

			if (result == System.Windows.Forms.DialogResult.OK && !string.IsNullOrWhiteSpace(fbd.SelectedPath))
			{
				try
				{
					XDocument noresident = XDocument.Load(fbd.SelectedPath + "\\NORESIDENT\\carto.xml");
					XNamespace ns = noresident.Root.Name.Namespace;
					XElement folder = noresident
						.Descendants(ns + "WMS_Capabilities_config").Single()
						.Elements(ns + "MapData").Single()
						.Elements(ns + "Folder").Single();
					folder.Value = fbd.SelectedPath;
					noresident.Save(tacview.AddOns.Current.GetPath() + "\\ESIOCServer_1.0.2\\noresident.xml");
					findNoResidentMission = true;
				}
				catch
				{
					tacview.Log.Info("Pas de Mission Non residente trouve.");
					findNoResidentMission = false;
				}

				try
				{
					XDocument resident = XDocument.Load(fbd.SelectedPath + "\\RESIDENT\\carto.xml");
					XNamespace ns = resident.Root.Name.Namespace;
					XElement folder = resident
						.Descendants(ns + "WMS_Capabilities_config").Single()
						.Elements(ns + "MapData").Single()
						.Elements(ns + "Folder").Single();
					folder.Value = fbd.SelectedPath;
					resident.Save(tacview.AddOns.Current.GetPath() + "\\ESIOCServer_1.0.2\\resident.xml");
					findResidentMission = true;
				}
				catch
				{
					tacview.Log.Info("Pas de Mission residente trouve.");
					findResidentMission = false;
				}

				if (findNoResidentMission | findResidentMission)
				{
					// check if TCP port is already in use
					this.process = new Process();
					this.process.StartInfo.WorkingDirectory = tacview.AddOns.Current.GetPath() + "\\ESIOCServer_1.0.2\\";
					//this.process.StartInfo.FileName = tacview.AddOns.Current.GetPath() + "\\ESIOCServer_1.0.2\\startServer.bat";

					this.process.StartInfo.FileName = tacview.AddOns.Current.GetPath() + "\\ESIOCServer_1.0.2\\JRE\\bin\\java.exe";
					this.process.StartInfo.Arguments = "-Xmx3g -Xms2g -Dcom.luciad.raster.signalReadFailure=true -Djava.io.tmpdir=./tmp/ -Dcom.luciad.format.raster.TLcdECWModelDecoder.retryTimeOut=60 -Dlogback.configurationFile=./resources/logback.xml -cp ESIOCServer/resources;ESIOCServer/lib/* samples.esioc.server.StartServer --webapp";
					this.process.StartInfo.CreateNoWindow = true;
					//this.process.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
					try
					{
						this.process.Start();
					}
					catch
					{
						tacview.Log.Info("Impossible de lancer le server.");

						ret = false;
					}
				}
				else
				{
					ret = false;
				}
			}
			return ret;
		}
		public void stopEsiocServer()
		{
			if (this.process != null)
			{
				try
				{
					this.process.Kill();
				}
				catch
				{

				}
				this.process = null;
			}

		}

		public void Event_SelectionChange(object sender, RoutedEventArgs e)
		{
			DownloadButton.IsEnabled = ListboxMaps.SelectedItems.Count > 0;
		}

		public void isEnableDwnloadButon(bool isEnable)
		{
			this.Dispatcher.Invoke(() =>
			{
				DownloadButton.IsEnabled = isEnable;
			});

		}
	}
}
