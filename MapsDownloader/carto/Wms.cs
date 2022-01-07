

namespace M2000D.carto
{
    using System;
    using System.Collections.Generic;
    using System.Collections.Specialized;
    using System.Drawing;
    using System.Drawing.Drawing2D;
    using System.Drawing.Imaging;
    using System.IO;
    using System.Linq;
    using System.Net;
    using System.Net.Http;
    using System.Text;
    using System.Threading;
    using System.Threading.Tasks;
    using TacviewSDK;
    using System.Windows.Controls;
    using Image = System.Drawing.Image;
    using System.Web;
    using System.Collections;
    using System.Xml.Linq;
    using Maps_Downloader.carto;
    using System.Windows;

    class Wms
    {
        private TacviewSDK.Wrapper tacview;
        private static long titlesTotal;
        private static long tilesDownloaded = 0;
        private static long tilesSkipped = 0;

        private static long layerTotal;
        private static long layerDownloaded = 0;

        public double MaxX { get; private set; }
        public double MaxY { get; private set; }
        public double MinX { get; private set; }
        public double MinY { get; private set; }

        private double resolution;

        private Wrapper.LogClass log { get; set; }

        private Thread downloadServiceThread;
        private string layer;
        private DownloadMaps downloadMaps;
        private Thread getLayerListThread;
        private IList selectedItems;
        private string urlOfSelectedServer;
        public string[] layers { get; set; }

        public Action LoadMaps { get; }

        private List<string> listSrsCrs = new List<string>();

        public Wms(Wrapper tacview, string urlOfSelectedServer, DownloadMaps downloadMapsUiForm)
        {
            this.tacview = tacview;
            this.urlOfSelectedServer = urlOfSelectedServer;
            this.downloadMaps = downloadMapsUiForm;
            getLayerListThread = new Thread(new ThreadStart(GetCapabilities));
            getLayerListThread.Start();
        }

        ~Wms()
        {
            if (this.getLayerListThread != null)
            {
                this.getLayerListThread.Abort();
                this.getLayerListThread = null;
            }
        }

        private void GetCapabilities()
        {
            HttpClient client = new HttpClient();
            //Pour pouvoir telecharger sur geoportail
            client.DefaultRequestHeaders.UserAgent.ParseAdd("Mozilla/5.0 (compatible; AcmeInc/1.0)");
            string url = this.urlOfSelectedServer + "?REQUEST=GetCapabilities&SERVICE=WMS";
            if (this.urlOfSelectedServer.Contains("wmts"))
                url = this.urlOfSelectedServer + "?REQUEST=GetCapabilities&SERVICE=WMTS";

            //specify to use TLS 1.2 as default connection
            if (url.Contains("https"))
            {
                System.Net.ServicePointManager.SecurityProtocol |= SecurityProtocolType.Tls12 | SecurityProtocolType.Tls11 | SecurityProtocolType.Tls;

            }
            HttpResponseMessage response;
            string capabilitiesXml = "";

            do
            {
                try
                {
                    response = client.GetAsync(url).Result;
                    if (response.StatusCode != HttpStatusCode.InternalServerError &&
                        response.Content.Headers.ContentType.MediaType != "application/vnd.ogc.se_xml")
                    {
                        capabilitiesXml = response.Content.ReadAsStringAsync().Result;
                    }
                }
                catch (Exception e)
                {
                    tacview.Log.Error(e.ToString());
                    Thread.Sleep(1000);
                }
            } while (capabilitiesXml.Length <= 0);

            XDocument xdoc = XDocument.Parse(capabilitiesXml);
            XNamespace ns = xdoc.Root.Name.Namespace;
            this.Version = (string)xdoc.Root.Attribute("version");
            IEnumerable<XElement> found = xdoc.Descendants(ns + "Capability").Elements(ns + "Layer").Elements(ns + "Layer");
            string service = "";
            string title = "";
            foreach (XElement p in found)
            {
                service += (string)p.Element(ns + "Name") + ";";
                title += (string)p.Element(ns + "Title") + ";";
            }
            if (service.Count() > 0)
                service.Remove(service.Length - 1);
            this.layers = service.Split(';');

            foreach (string layer in this.layers)
            {
                this.downloadMaps.Dispatcher.Invoke(() =>
                {
                    this.downloadMaps.ListboxMaps.Items.Add(layer);
                });
            }
            IEnumerable<XElement> foundSrsCrs;
            switch (this.Version)
            {
                case "1.1.1":
                    foundSrsCrs = xdoc.Descendants(ns + "SRS");
                    break;
                case "1.3.0":
                    foundSrsCrs = xdoc.Descendants(ns + "CRS");
                    break;
                default:
                    throw new ArgumentException("WMS Version invalid.");
            }

            foreach (string srsCrs in foundSrsCrs)
            {
                if (!this.listSrsCrs.Contains(srsCrs))
                    this.listSrsCrs.Add(srsCrs);
            }

            if (this.listSrsCrs.Contains("CRS:84"))
            {
                this.SrsCrs = "CRS:84";
            }
            else
            {
                if (this.listSrsCrs.Count > 0)
                    this.SrsCrs = this.listSrsCrs.First();
            }
        }





        public void DownloadService(IList selectedItems, double topLeftLatitude, double topLeftLongitude, double bottomRightLatitude, double bottomRightLongitude)
        {
            DownloadService(selectedItems, topLeftLatitude, topLeftLongitude, bottomRightLatitude, bottomRightLongitude, 0.1);
        }
        public void DownloadService(IList selectedItems, double topLeftLatitude, double topLeftLongitude, double bottomRightLatitude, double bottomRightLongitude, double resolution)
        {
            this.selectedItems = selectedItems;
            this.log = tacview.Log;
            titlesTotal = 0;
            tilesDownloaded = 0;
            tilesSkipped = 0;

            this.MaxX = Math.Max(topLeftLongitude, bottomRightLongitude);
            this.MaxY = Math.Max(topLeftLatitude, bottomRightLatitude);
            this.MinX = Math.Min(topLeftLongitude, bottomRightLongitude);
            this.MinY = Math.Min(topLeftLatitude, bottomRightLatitude);
            this.resolution = resolution;
            this.downloadServiceThread = new Thread(new ThreadStart(DownloadServiceThread));
            this.downloadServiceThread.Start();
        }

        public void StopDownloadService()
        {
            if (downloadServiceThread != null)
            {
                this.downloadServiceThread.Abort();
            }
        }

        private void DownloadServiceThread()
        {
            if (!Directory.Exists(Settings.OutputPath))
            {
                log.Error("Output directory not found.");
            }
            else
            {
                layerTotal = this.selectedItems.Count;
                foreach (string item in this.selectedItems)
                {
                    this.layer = item;
                    tilesDownloaded = 0;
                    tilesSkipped = 0;

                    List<double> cols = new List<double>();
                    Math.Max(1, 1);
                    for (double i = this.MinX; i < this.MaxX; i += this.resolution)
                    {
                        cols.Add(i);
                    }

                    List<double> rows = new List<double>();
                    for (double i = this.MinY; i < this.MaxY; i += this.resolution)
                    {
                        rows.Add(i);
                    }

                    titlesTotal = cols.Count * rows.Count;

                    downloadMaps.isEnableDwnloadButon(false);

                    Parallel.ForEach(cols, new ParallelOptions { MaxDegreeOfParallelism = Settings.DegreeOfParallelism }, x =>
                    {
                        double ratio = 0;


                        foreach (double y in rows)
                        {

                            string topLeftLat = "";
                            string topLeftLon = "";
                            string bottomRightLat = "";
                            string bottomRightLon = "";
                            if ((y + this.resolution) < 0)
                            {
                                topLeftLat = string.Format("S{0:0000}", (y + this.resolution) * -100);
                            }
                            else
                            {
                                topLeftLat = string.Format("N{0:0000}", (y + this.resolution) * 100);
                            }
                            if (y < 0)
                            {
                                bottomRightLat = string.Format("S{0:0000}", y * -100);
                            }
                            else
                            {
                                bottomRightLat = string.Format("N{0:0000}", y * 100);
                            }

                            if (x < 0)
                            {
                                topLeftLon = string.Format("O{0:00000}", x * -100);
                            }
                            else
                            {
                                topLeftLon = string.Format("E{0:00000}", x * 100);
                            }
                            if (x + this.resolution < 0)
                            {
                                bottomRightLon = string.Format("O{0:00000}", (x + this.resolution) * -100);
                            }
                            else
                            {
                                bottomRightLon = string.Format("E{0:00000}", (x + this.resolution) * 100);
                            }

                            string serviceName = new string(this.layer.ToCharArray().Where(c => !('.' == c || '-' == c)).ToArray());
                            string filename = Path.Combine(Settings.OutputPath, $"{serviceName}-{topLeftLat}{topLeftLon}-{bottomRightLat}{bottomRightLon}T");

                            string imgfileName = filename;

                            if (!File.Exists(imgfileName))
                            {
                                // bool hd = this.layer.ToUpper().Contains("SAT") | this.layer.ToUpper().Contains("ORTHO");
                                bool result = DownloadTile(x, y, imgfileName);

                                if (result)
                                {
                                    Interlocked.Increment(ref tilesDownloaded);
                                }
                                else
                                {
                                    Interlocked.Increment(ref tilesSkipped);
                                }

                            }
                            if (this.downloadMaps != null)
                            {
                                DisplayProgress(this.downloadMaps);
                            }
                            DisplayProgress(this.log);
                        }
                    });


                    downloadMaps.isEnableDwnloadButon(true);

                    log.Info("Download finished.");
                    Interlocked.Increment(ref layerDownloaded);
                    DisplayProgress(this.downloadMaps);

                }
            }
        }

        public static double ProgressLayers
        {
            get
            {
                if (layerTotal == 0)
                    return 0;
                return (double)(layerDownloaded) / layerTotal * 100;
                //return 0.0;
            }
        }
        public static double ProgressTitles
        {
            get
            {
                if (titlesTotal == 0)
                    return 0;
                return (double)(tilesDownloaded + tilesSkipped) / titlesTotal * 100;
            }
        }

        public string Version { get; private set; }
        public string SrsCrs { get; private set; }

        private static void DisplayProgress(Wrapper.LogClass log)
        {
            log.Info($"\r{tilesDownloaded} downloaded, {tilesSkipped} skipped, {titlesTotal} total. Progress: {ProgressTitles:0.00} %");
        }
        private static void DisplayProgress(ProgressBar progress2)
        {
            progress2.Dispatcher.Invoke(() =>
            {
                progress2.Value = ProgressTitles;
            });
        }
        private void DisplayProgress(DownloadMaps downloadMaps)
        {
            downloadMaps.Dispatcher.Invoke(() =>
            {
                downloadMaps.progress2.Value = ProgressTitles;
                downloadMaps.progress1.Value = ProgressLayers;
                downloadMaps.DownloadButton.IsEnabled = !this.downloadServiceThread.IsAlive;
            });
        }


        /// <summary>
        /// Telecharge la tuile sur la zone selectionner
        /// </summary>
        /// <param name="x"> fournir la lattide </param>
        /// <param name="y"> fournir la longitude</param>
        /// <param name="filename">Nom du fichier de sorti</param>
        /// <param name="downloadSD">Creer une image basse resolution 50% de l'original</param>
        /// <returns></returns>
        private bool DownloadTile(double x, double y, string filename)
        {
            HttpClient client = new HttpClient();
            client.DefaultRequestHeaders.UserAgent.ParseAdd("Mozilla/5.0 (compatible; AcmeInc/1.0)");
            string url = GetWmsUrl(x, y);
            try
                {
                HttpResponseMessage response = client.GetAsync(url).Result;

                if (response.StatusCode != HttpStatusCode.InternalServerError &&
                    response.Content.Headers.ContentType.MediaType != "application/vnd.ogc.se_xml")
                {
                    Stream result = response.Content.ReadAsStreamAsync().Result;
                    Image image = Image.FromStream(result);

                    switch (Settings.Wms.ImageFormat)
                    {
                        case ImageEnum.Jpg:
                            image.Save(filename + ".jpg", ImageFormat.Jpeg);
                            break;
                        case ImageEnum.Png:
                            image.Save(filename + ".png", ImageFormat.Png);
                            break;
                    }
                    return true;
                }

                return false;
            }
            catch
            {
                return false;
            }
        }


        /// <summary>
        /// Resize the image to the specified width and height.
        /// </summary>
        /// <param name="image">The image to resize.</param>
        /// <param name="width">The width to resize to.</param>
        /// <param name="height">The height to resize to.</param>
        /// <returns>The resized image.</returns>
        public static Bitmap ResizeImage(Image image, int width, int height)
        {
            var destRect = new Rectangle(0, 0, width, height);
            var destImage = new Bitmap(width, height);

            destImage.SetResolution(image.HorizontalResolution, image.VerticalResolution);

            using (var graphics = Graphics.FromImage(destImage))
            {
                graphics.CompositingMode = CompositingMode.SourceCopy;
                graphics.CompositingQuality = CompositingQuality.HighQuality;
                graphics.InterpolationMode = InterpolationMode.HighQualityBicubic;
                graphics.SmoothingMode = SmoothingMode.HighQuality;
                graphics.PixelOffsetMode = PixelOffsetMode.HighQuality;

                using (var wrapMode = new ImageAttributes())
                {
                    wrapMode.SetWrapMode(WrapMode.TileFlipXY);
                    graphics.DrawImage(image, destRect, 0, 0, image.Width, image.Height, GraphicsUnit.Pixel, wrapMode);
                }
            }

            return destImage;
        }

        internal void setUiForm(DownloadMaps downloadMaps)
        {
            this.downloadMaps = downloadMaps;
        }

        private string GetWmsUrl(double longitude, double lattitude)
        {


            // x = long
            //y = latt
            // double ratio = getRationWithHeightTitle(lattitude, longitude);


            double xBottomLeft = longitude;
            double yBottomLeft = lattitude;
            double xTopRight = longitude + this.resolution;
            double yTopRight = lattitude + this.resolution;

            double ratio = getRationWithHeightTitle(xBottomLeft, yBottomLeft, xTopRight, yTopRight);

            if (this.SrsCrs.Equals("EPSG:900913"))
            {
                System.Windows.Point bottomLeft = WebMercator.LatLonToMeters(yBottomLeft, xBottomLeft);
                System.Windows.Point topRight = WebMercator.LatLonToMeters(yTopRight, xTopRight);
                xBottomLeft = bottomLeft.X;
                yBottomLeft = bottomLeft.Y;
                xTopRight = topRight.X;
                yTopRight = topRight.Y;
            }


            var nlBE = new System.Globalization.CultureInfo("us-US");
            nlBE.NumberFormat.CurrencyGroupSeparator = ".";
            System.Threading.Thread.CurrentThread.CurrentCulture = nlBE;

            NameValueCollection parameters;
            parameters = new NameValueCollection
            {
                { "service", "WMS" },
                { "request", "GetMap" },
                { "layers", this.layer},
                { "styles", Settings.Wms.Styles },
                { "height", Settings.Grid.Height.ToString() },
                { "width", (((int)(Settings.Grid.Height*ratio))).ToString() }
            };


            switch (Settings.Wms.ImageFormat)
            {
                case ImageEnum.Jpg:
                    parameters.Add("format", "image/jpeg");
                    break;
                case ImageEnum.Png:
                    parameters.Add("format", "image/png");
                    parameters.Add("transparent", Settings.Wms.Transparency);
                    break;
                default:
                    throw new ArgumentException("Image Format invalid.");
            }

            switch (this.Version)
            {
                case "1.1.1":
                    parameters.Add("version", "1.1.1");
                    parameters.Add("srs", this.SrsCrs);
                    parameters.Add("bbox", $"{xBottomLeft},{yBottomLeft},{xTopRight},{yTopRight}");
                    break;
                case "1.3.0":
                    parameters.Add("version", "1.3.0");
                    parameters.Add("crs", this.SrsCrs);
                    parameters.Add("bbox", $"{xBottomLeft},{yBottomLeft},{xTopRight},{yTopRight}");
                    string test = parameters["bbox"].ToString();
                    break;
                default:
                    throw new ArgumentException("WMS Version invalid.");
            }

            string baseUrl = this.urlOfSelectedServer + "?";
            string queryString = string.Join("&",
            (from key in parameters.AllKeys
             from value in parameters.GetValues(key)
             select string.Format("{0}={1}", HttpUtility.UrlEncode(key), System.Web.HttpUtility.UrlEncode(value))).ToArray());

            return baseUrl + queryString;
        }

        private static bool IsWhite(Bitmap scrBitmap)
        {
            Color colorWhite = Color.White;
            Bitmap newBitmap = new Bitmap(scrBitmap.Width, scrBitmap.Height);
            for (int i = 0; i < scrBitmap.Width; i++)
            {
                for (int j = 0; j < scrBitmap.Height; j++)
                {
                    Color pixel = scrBitmap.GetPixel(i, j);

                    if (!(colorWhite.R == pixel.R && colorWhite.G == pixel.G && colorWhite.B == pixel.B))
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        private static Bitmap ChangeColor(Bitmap scrBitmap)
        {
            Color actualColor = Settings.ImageColors.FromColor;
            Color newColor = Settings.ImageColors.ToColor;

            Bitmap newBitmap = new Bitmap(scrBitmap.Width, scrBitmap.Height);
            for (int i = 0; i < scrBitmap.Width; i++)
            {
                for (int j = 0; j < scrBitmap.Height; j++)
                {
                    Color pixel = scrBitmap.GetPixel(i, j);

                    if (actualColor.R == pixel.R && actualColor.G == pixel.G && actualColor.B == pixel.B)
                    {
                        newBitmap.SetPixel(i, j, newColor);
                    }
                    else
                    {
                        newBitmap.SetPixel(i, j, pixel);
                    }
                }
            }

            return newBitmap;
        }

        private double getDistanceFromLatLonInKm(double lat1, double lon1, double lat2, double lon2)
        {
            int R = 6371; // Radius of the earth in km
            double dLat = deg2rad(lat2 - lat1);  // deg2rad below
            double dLon = deg2rad(lon2 - lon1);
            double a =
              Math.Sin(dLat / 2) * Math.Sin(dLat / 2) +
              Math.Cos(deg2rad(lat1)) * Math.Cos(deg2rad(lat2)) *
              Math.Sin(dLon / 2) * Math.Sin(dLon / 2);
            var c = 2 * Math.Atan2(Math.Sqrt(a), Math.Sqrt(1 - a));
            var d = R * c; // Distance in km
            return d;
        }

        /// <summary>
        /// Recuppere la ration horizontal vertical des tuile pour compenser 
        /// la deformation de la planete
        /// </summary>
        /// <param name="latitude">Latitude</param>
        /// <param name="longitude">Longitude</param>
        /// <returns></returns>
        private double getRationWithHeightTitle(double latitude, double longitude)
        {
            double ret = 0;
            double distanceHorizontal = tacview.Math.Vector.GetDistanceOnEarth(longitude, latitude, longitude + resolution, latitude, 0);
            double distanceVertical = tacview.Math.Vector.GetDistanceOnEarth(longitude, latitude, longitude, latitude + resolution, 0);
            ret = distanceHorizontal / distanceVertical;
            //  tacview.Math.Vector.LongitudeLatitudeToCartesian(test);
            //	tacview.Telemetry.GetCurrentTransform()
            return ret;
        }

        private double getRationWithHeightTitle(double xBottomLeft, double yBottomLeft, double xTopRight, double yTopRight)
        {
            double distanceHorizontal = tacview.Math.Vector.GetDistanceOnEarth(deg2rad(xBottomLeft), deg2rad(yBottomLeft), deg2rad(xTopRight), deg2rad(yBottomLeft), 0);
            double distanceVertical = tacview.Math.Vector.GetDistanceOnEarth(deg2rad(xBottomLeft), deg2rad(yBottomLeft), deg2rad(xBottomLeft), deg2rad(yTopRight), 0);
            double ret = distanceHorizontal / distanceVertical;

            //tacview.Log.Info(
            //    "Long : " + xBottomLeft + " Lat top left " + yBottomLeft + 
            //    " Long top right " + xTopRight + "Lat top right " + yTopRight + 
            //    " Distance horizontal :" + distanceHorizontal + " Distance vertical "+ distanceVertical+
            //    " ratio " + ret);
            return ret;
        }

        private double deg2rad(double deg)
        {
            return deg * (Math.PI / 180);
        }

    }

}
