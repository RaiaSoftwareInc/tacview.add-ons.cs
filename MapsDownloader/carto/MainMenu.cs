using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Interop;
using TacviewSDK;

namespace M2000D.carto
{
    class MainMenu
    {
        private int mapsMenuID;
        public Dictionary<string, string> ogcServerList { get; set; }
        public Wrapper tacview { get; set; }
        private int downloadMenuID;
        private int chooseServerMenuID;
        private DownloadMaps uiDownloadMaps;
        private AddOgcServer uiAddogcserver;
        private SelectOgcServer uiSelectOgcServer;
        private DeleteOgcServer uiDeleteOgcServer;

        public string selectedServer {get; set;}
        public Action LoadMaps { get; }

        public MainMenu(Wrapper tacview, int mainMenuID,ref Dictionary<string, string> ogcServerList)
        {
            this.mapsMenuID = mainMenuID;
            this.ogcServerList = ogcServerList;
            this.tacview = tacview;
            this.selectedServer = "";
            createMenu(mainMenuID);
        }

        public MainMenu(Wrapper tacview, int mainMenuID, ref Dictionary<string, string> ogcServerList, Action loadMaps) : this(tacview, mainMenuID, ref ogcServerList)
        {
            LoadMaps = loadMaps;
        }

        private void createMenu(int mainMenuID)
        {
            this.mapsMenuID = mainMenuID;
            this.downloadMenuID = tacview.UI.Menus.AddCommand(this.mapsMenuID, "Download Titles..", displayDownloadMaps);
            tacview.UI.Menus.AddCommand(this.mapsMenuID, "Delete All Title..", deleteMaps);
            tacview.UI.Menus.AddSeparator(this.mapsMenuID);
            this.tacview.UI.Menus.AddCommand(mapsMenuID, "Add server", displayAddServerUI);
            this.chooseServerMenuID = this.tacview.UI.Menus.AddCommand(this.mapsMenuID, "Select server",displaySelectServerUI);
            this.tacview.UI.Menus.AddCommand(this.mapsMenuID, "Delete server", displayDeleteServerUI);
            //updateChooseServerMenu();
            this.tacview.UI.Menus.AddSeparator(this.mapsMenuID);
            settingsReadWmsServerList();
            settingsReadSelectedServer();
        }

        private void deleteMaps(int commandId)
        {
            DirectoryInfo di = new DirectoryInfo(Settings.OutputPath);
            IEnumerable<FileInfo> FilesList = di.GetFiles("*-???????????-???????????T*").Where(s => Settings.supportedExtensions.Contains(s.Extension.ToLower()));

            int numberTotalOfFile = FilesList.Count();
            int i = 0;
            foreach (FileInfo File in FilesList)
            {
                File.Delete();
                tacview.Terrain.HideCustomTexture(File.Name);
                i++;
                int percent = (100 * i) / numberTotalOfFile;
                if ((percent % 5) == 0)
                {
                    tacview.Log.Info("Pourcentage fichier suprime = "+percent+" %");
                }
            }
            LoadMaps();

        }

            private void displayAddServerUI(int commandId)
        {
            if (this.uiAddogcserver == null || !this.uiAddogcserver.IsLoaded)
            {
                this.uiAddogcserver = new AddOgcServer();
                uiAddogcserver.setParent(this);
                WindowInteropHelper windowWrapper = new WindowInteropHelper(uiAddogcserver);
                windowWrapper.Owner = this.tacview.UI.GetWindowHandle();
                uiAddogcserver.ShowInTaskbar = false;
                uiAddogcserver.ResizeMode = System.Windows.ResizeMode.CanResize;
            }
            uiAddogcserver.Show();
        }

        private void displaySelectServerUI(int commandId)
        {
            if (this.uiSelectOgcServer == null || !this.uiSelectOgcServer.IsLoaded)
            {
                this.uiSelectOgcServer = new SelectOgcServer();
                uiSelectOgcServer.setParent(this);
                WindowInteropHelper windowWrapper = new WindowInteropHelper(uiSelectOgcServer);
                windowWrapper.Owner = this.tacview.UI.GetWindowHandle();
                uiSelectOgcServer.ShowInTaskbar = false;
            }
            uiSelectOgcServer.Show();
        }

        private void displayDeleteServerUI(int commandId)
        {
            if (this.uiDeleteOgcServer == null || !this.uiDeleteOgcServer.IsLoaded)
            {
                this.uiDeleteOgcServer = new DeleteOgcServer();
                uiDeleteOgcServer.setParent(this);
                WindowInteropHelper windowWrapper = new WindowInteropHelper(uiDeleteOgcServer);
                windowWrapper.Owner = this.tacview.UI.GetWindowHandle();
                uiDeleteOgcServer.ShowInTaskbar = false;
            }
            uiDeleteOgcServer.Show();
        }

        private void displayDownloadMaps(int commandId)
        {
            if (this.uiDownloadMaps == null || !this.uiDownloadMaps.IsLoaded)
            {
                this.uiDownloadMaps = new DownloadMaps(LoadMaps);
                uiDownloadMaps.setParent(this);
                WindowInteropHelper windowWrapper = new WindowInteropHelper(uiDownloadMaps);
                windowWrapper.Owner = this.tacview.UI.GetWindowHandle();
                uiDownloadMaps.ShowInTaskbar = false;
            }
            uiDownloadMaps.Show();
        }

        public void addServer(string name, string url)
        {
            this.ogcServerList.Add(name, url);
            settingsSaveServerList();
        }

        public void settingsSaveServerList()
        {
            string serverListString = "";
            foreach (KeyValuePair<string, string> ogcServer in ogcServerList)
            {
                serverListString += ogcServer.Key + "," + ogcServer.Value + ";";
            }
            serverListString = serverListString.Remove(serverListString.Length - 1);

            tacview.AddOns.Current.Settings.SetString("ServerList", serverListString);
        }
        internal void Shutdown()
        {
            if (this.uiAddogcserver != null)
            {
                this.uiAddogcserver.Close();
                this.uiAddogcserver = null;
            }
            if (this.uiSelectOgcServer != null)
            {
                this.uiSelectOgcServer.Close();
                this.uiSelectOgcServer = null;
            }
            if (this.uiDeleteOgcServer != null)
            {
                this.uiDeleteOgcServer.Close();
                this.uiDeleteOgcServer = null;
            }
            if (this.uiDownloadMaps != null)
            {
                this.uiDownloadMaps.Close();
                this.uiDownloadMaps = null;
            }
            if (this.ogcServerList != null)
            {
                this.ogcServerList = null;
            }
        }

        private void settingsReadWmsServerList()
        {
            string serverList = tacview.AddOns.Current.Settings.GetString("ServerList", 
                "Geoportail,https://wxs.ign.fr/essentiels/geoportail/r/wms;" +
                "Openaip,https://1.tile.maps.openaip.net/geowebcache/service/wms;" +
                "OpenStreetmap,http://ows.terrestris.de/osm/service;" +
                "");
            if (serverList.Length > 0)
            {
                string[] serverListArray = serverList.Split(';');
                foreach (string serverNameAdresse in serverListArray)
                {
                    string[] server = serverNameAdresse.Split(',');
                    this.ogcServerList.Add(server[0], server[1]);
                }
            }
        }

        internal void settingsSaveSelectedServer(string selectedServer)
        {
            this.tacview.AddOns.Current.Settings.SetString("SelectedServer", selectedServer);
            this.selectedServer = selectedServer;
        }

        internal void settingsReadSelectedServer()
        {
            this.selectedServer = this.tacview.AddOns.Current.Settings.GetString("SelectedServer", "Geoportail");
        }
    }
}
