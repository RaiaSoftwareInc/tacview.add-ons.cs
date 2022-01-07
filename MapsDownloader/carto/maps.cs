using System;
using System.IO;

using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Net.Http;
using System.Net;
using System.Threading;

namespace M2000D.carto
{
    using ObjectHandle = System.IntPtr;

    class maps
    {
        private readonly TacviewSDK.Wrapper tacview;
        private TacviewSDK.Wrapper.TelemetryClass telemetry;
        private Dictionary<string, Carte> cartes;
        private Dictionary<int, string> menuDownloadMapID;
        private Dictionary<string, string> ogcServerList;
        private MainMenu mainMenu;


        /// <summary>
        /// Class permetant l'importation des cartes
        /// </summary>
        /// <param name="tacviewWrapper"></param>
        public maps(TacviewSDK.Wrapper tacviewWrapper, int mainMenuID)
        {
            this.tacview = tacviewWrapper;
            this.telemetry = tacview.Telemetry;
            this.menuDownloadMapID = new Dictionary<int, string>();
            this.ogcServerList = new Dictionary<string, string>();
            this.tacview.UI.Renderer.ContextMenu.Listeners += OnContextMenu;
            mainMenu = new MainMenu(tacview, mainMenuID, ref this.ogcServerList, loadMaps);

            //createMenu(mainMenuID);
            loadMaps();
        }
        ~maps()
        {


        }

        /// <summary>
        /// Shutdown all process 
        /// </summary>
        internal void Shutdown()
        {
            if (this.mainMenu != null)
            {
                this.mainMenu.Shutdown();
                this.mainMenu = null;
            }
        }

        /// <summary>
        /// Loads Maps 
        /// </summary>
        private void loadMaps()
        {
            string selectedMpap = tacview.AddOns.Current.Settings.GetString("SelectedMap", "");
            this.cartes = new Dictionary<string, Carte>();
            
            DirectoryInfo di = new DirectoryInfo(Settings.OutputPath);
            IEnumerable<FileInfo> FilesList = di.GetFiles("*-???????????-???????????T*").Where(s => Settings.supportedExtensions.Contains(s.Extension.ToLower()));

             foreach (FileInfo File in FilesList)
            {
                double topLeftLongitude = 0;
                double topLeftLatitude = 0;
                double bottomRightLongitude = 0;
                double bottomRightLatitude = 0;

                parseDalleFromFileName(File.Name, out topLeftLatitude, out topLeftLongitude, out bottomRightLatitude, out bottomRightLongitude, out string layer);

                if (!this.cartes.ContainsKey(layer))
                {
                    this.cartes.Add(layer, new Carte());
                    this.cartes[layer].Layer = layer;
                }
                this.cartes[layer].titles.Add(new Title(File.Name, File.Name, topLeftLatitude, topLeftLongitude,bottomRightLatitude,bottomRightLongitude));

                tacview.Terrain.AddCustomTexture(File.Name, "Real World", File.FullName, null
                    , topLeftLongitude, topLeftLatitude
                    , bottomRightLongitude, topLeftLatitude
                    , bottomRightLongitude, bottomRightLatitude
                    , topLeftLongitude, bottomRightLatitude);
                tacview.Terrain.HideCustomTexture(File.Name);
            }

            if (this.cartes.ContainsKey(selectedMpap))
            {
                displayMap(selectedMpap);
            }
        }

        /// <summary>
        /// Retourne coordinate and layer from the file jpg 
        /// </summary>
        /// <param name="fileName"> nom du  fichier</param>
        /// <param name="topLeftLatitude">return latirude of the uper top left corner</param>
        /// <param name="topLeftLongitude">return longitude of the uper top left corner</param>
        /// <param name="layer">return the layer name</param>
        /// <returns></returns>
        private bool parseDalleFromFileName(string fileName, out double topLeftLatitude, out double topLeftLongitude, out double bottomRightLatitude, out double bottomRightLongitude, out string layer)
        {
            bool ret = false;

            double topLeftLat = 0;
            double topLeftLong = 0;
            double bottomRightLat = 0;
            double bottomRightLong = 0;
            string[] subs = fileName.Split('-');

            layer = subs[0];

            try
            {
                topLeftLat = Convert.ToDouble(subs[1].Substring(1, 4)) / 100;
                topLeftLong = Convert.ToDouble(subs[1].Substring(6, 5)) / 100;
                bottomRightLat = Convert.ToDouble(subs[2].Substring(1, 4)) / 100;
                bottomRightLong = Convert.ToDouble(subs[2].Substring(6, 5)) / 100;
            }
            catch (FormatException)
            {
                tacview.Log.Error("Unable to convert '{subs[1].Substring(1, 2)}' or '{subs[1].Substring(4, 3)}' to a Double.");
            }
            catch (OverflowException)
            {
                tacview.Log.Error("'{subs[1].Substring(1, 2)}' or '{subs[1].Substring(4, 3)}' is outside the range of a Double.");
            }
            finally
            {
                if (subs[1].Substring(0, 1).StartsWith("S"))
                {
                    topLeftLat = topLeftLat * -1;
                }
                if (subs[1].Substring(5, 1).StartsWith("O"))
                {
                    topLeftLong = topLeftLong * -1;
                }
                if (subs[2].Substring(0, 1).StartsWith("S"))
                {
                    bottomRightLat = bottomRightLat * -1;
                }
                if (subs[2].Substring(5, 1).StartsWith("O"))
                {
                    bottomRightLong = bottomRightLong * -1;
                }
                topLeftLatitude = Tools.ConvertDegreesToRadians(topLeftLat);
                topLeftLongitude = Tools.ConvertDegreesToRadians(topLeftLong);
                bottomRightLatitude = Tools.ConvertDegreesToRadians(bottomRightLat);
                bottomRightLongitude = Tools.ConvertDegreesToRadians(bottomRightLong);
                ret = true;
            }

            return ret;
        }

        /// <summary>
        /// Create Context Menu 
        /// </summary>
        /// <param name="contextMenuId"></param>
        /// <param name="objectHandle"></param>
        private void OnContextMenu(int contextMenuId, ObjectHandle objectHandle)
        {
            int menu = tacview.UI.Menus.AddMenu(contextMenuId, "Maps");
            //tacview.UI.Menus.AddCommand(menu, "Reload Maps", reloadMaps);
            //int subMenu1 = tacview.UI.Menus.AddMenu(menu, "Display Hide Maps");
            //tacview.UI.Menus.AddCommand(subMenu1, "Affiche debug", displayDebug);
            //tacview.UI.Menus.AddCommand(subMenu1, "Cacher debug", hideDebug);
            Dictionary<string, Carte>.Enumerator cartesEnum = this.cartes.GetEnumerator();
            while (cartesEnum.MoveNext())
            {
                KeyValuePair<string, Carte> carte = cartesEnum.Current;
                int menuID = tacview.UI.Menus.AddOption(menu, carte.Key, carte.Value.Selected, changeMap);
                tacview.Log.Info("Menu ID " + carte.Key + " = " + menuID);
                carte.Value.menuID = menuID;

            }

        }

        /// <summary>
        ///  Switch beetween to mapq
        /// </summary>
        /// <param name="commandId">Id off the sub menu</param>
        private void changeMap(int commandId)
        {
            tacview.Log.Info("Value off command = " + commandId);
            Dictionary<string, Carte>.Enumerator cartesEnum = this.cartes.GetEnumerator();
            cartesEnum = this.cartes.GetEnumerator();
            while (cartesEnum.MoveNext())
            {
                KeyValuePair<string, Carte> carte = cartesEnum.Current;
                if (carte.Value.menuID == commandId)
                {
                    displayMap(carte.Key);
                }
                else
                {
                    hideMap(carte.Key);
                }
                
            }
        }

        /// <summary>
        /// Hide a map
        /// </summary>
        /// <param name="key">Key of the map to hide</param>
        private void hideMap(string key)
        {
            this.cartes[key].Selected = false;
            foreach (Title dalle in this.cartes[key].titles)
            {
                tacview.Terrain.HideCustomTexture(dalle.name);
            }
        }
        /// <summary>
        /// Display map
        /// </summary>
        /// <param name="key">Key of the map to display</param>
        private void displayMap(string key)
        {
            this.cartes[key].Selected = true;
            tacview.AddOns.Current.Settings.SetString("SelectedMap", key);

            foreach (Title dalle in this.cartes[key].titles)
            {
                tacview.Terrain.ShowCustomTexture(dalle.name);
            }
        }
    }

    /// <summary>
    /// Map object
    /// </summary>
    public class Carte
    {
        public string Layer { get; set; }
        public List<Title> titles { get; set; }
        /// <summary>
        /// Id of the subMenu
        /// </summary>
        public int menuID { get; set; }
        /// <summary>
        /// Status of selected map
        /// </summary>
        public bool Selected { get; internal set; }

        public Carte()
        {
            this.titles = new List<Title>();
        }
    }

    public class Title
    {
        public string filePath { get; set; }
        public string name { get; set; }
        public double topLeftlat { get; set; }
        public double topLeftlon { get; set; }
        public double bottomRightlat { get; set; }
        public double bottomRightlon { get; set; }
        public Title(string filePath, string name, double topLeftlat, double topLeftlon, double bottomRightlat, double bottomRightlon)
        {
            this.filePath = filePath;
            this.name = name;
            this.topLeftlat = topLeftlat;
            this.topLeftlon = topLeftlon;
            this.bottomRightlat = bottomRightlat;
            this.bottomRightlon = bottomRightlon;
        }
}

}
