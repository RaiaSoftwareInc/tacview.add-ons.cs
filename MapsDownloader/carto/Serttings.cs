
namespace M2000D.carto
{

    using System.Drawing;

    public static class Settings
    {
        // Maximum number of parallel threads 8
        public static int DegreeOfParallelism = 8;

        // Directory must exist and be writable
        public static string OutputPath = @"C:\\ProgramData\\Tacview\\Data\\Terrain\\Textures";

        /// <summary>
        /// List of supported etension
        /// </summary>
        public static string supportedExtensions = "*.jpg,*.gif,*.png,*.jpeg,*.tif,*.tiff";

        // Extent of the WMS layer that should be captured
        // Note: lower boundaries inclusive, upper boundaries exclusive
        // Extent and pixel size of each tile that shall be downloaded
        public static class Grid
        {

            public static int Height = 1000;

            public static int Width = 1000;
        }

        public static class ImageColors
        {
            // Any color correction necessary (e.g. make black pixels white)
            public static bool CorrectionNeeded = false;

            public static Color FromColor = Color.Black;

            public static Color ToColor = Color.White;
        }

        public static class Wms
        {
            // Format of the outpu image
            public static ImageEnum ImageFormat = ImageEnum.Png;

            public static string Styles = "";

            // True or False, only applies for ImageFormat Png
            public static string Transparency = "true";

        }
    }
}
