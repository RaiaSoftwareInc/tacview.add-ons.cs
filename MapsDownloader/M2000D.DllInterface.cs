/*
	Tacview.AddOn.Tutorial.HelloWorld.DllInterface
	Main entry point for C# addons.
	Version 1.7.3 // 2018-10-04
	Copyright (C) 2018 Raia Software. All rights reserved.

	NOTE: You need a licence of Tacview Enterprise to run C# addons.
*/

using System;
using System.Runtime.InteropServices;

namespace M2000D
{
    public class DllInterface
    {
        // TacviewAddOnInitialize is called by Tacview as soon as the DLL has been loaded.
        // This function must return true if everything is all right, otherwise Tacview will unload this DLL.

        [DllExport]
        static public bool TacviewAddOnInitialize(IntPtr addonHandle, IntPtr tacviewGetInterface)
        {


            // Initialize Tacview wrapper
            Tacview = new TacviewSDK.Wrapper();

            if (!Tacview.InitializeWrapper(addonHandle, tacviewGetInterface))
            {
                return false;
            }

            // Declare this addon properties so it is properly displayed in Tacview menus.
            var version = typeof(DllInterface).Assembly.GetName().Version;
            Tacview.AddOns.Current.SetTitle("Maps Downloader");
            Tacview.AddOns.Current.SetVersion(version.ToString());
            Tacview.AddOns.Current.SetAuthor("Gandy bruno");
            Tacview.AddOns.Current.SetNotes("Downloads map on WMS server.");

            // Now we ask Tacview to display specific information in its log window.

            int mainMenuID = Tacview.UI.Menus.AddMenu(0, "Maps Downloader");
            maps = new carto.maps(Tacview, mainMenuID);
            return true;
        }

        // TacviewAddOnShutdown() is called by Tacview right before unloading the DLL.
        // It is called only if Initialize() has been successful.
        // This is the best place to cleanup all resources allocated by your module.

        [DllExport]
        static public void TacviewAddOnShutdown()
        {

            //shutdown Carto
            if (maps != null)
            {
                maps.Shutdown();
                maps = null;
            }

            // Shutdown Tacview wrapper

            if (Tacview != null)
            {
                Tacview.ShutdownWrapper();
                Tacview = null;
            }


        }

        // Tacview API

        private static TacviewSDK.Wrapper Tacview;

        private static carto.maps maps;
    }


}
