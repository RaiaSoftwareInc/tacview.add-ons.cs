using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace M2000D.carto
{
    /// <summary>
    /// Logique d'interaction pour SelectOgcServer.xaml
    /// </summary>
    public partial class SelectOgcServer : Window
    {
        private MainMenu mainMenu = null;

        public SelectOgcServer()
        {
            InitializeComponent();
            
        }

        private void loadServer()
        {
           if(mainMenu != null) 
           {
                foreach(KeyValuePair<string,string> ogcserver in this.mainMenu.ogcServerList)
                {
                    serverNameCombobox.Items.Add(ogcserver.Key);
                }
                serverNameCombobox.SelectedItem = this.mainMenu.selectedServer;
           }
        }

        private void Ok_Click(object sender, RoutedEventArgs e)
        {
            if (mainMenu != null)
            {
                if(serverNameCombobox.SelectedItem != null) {
                    if (this.mainMenu.selectedServer != serverNameCombobox.Text)
                    {
                        this.mainMenu.settingsSaveSelectedServer(serverNameCombobox.Text);
                    }
                }
            }
            this.Close();
        }

        internal void setParent(MainMenu mainMenu)
        {
            this.mainMenu = mainMenu;
            loadServer();
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        internal void stopEsiocServer()
        {
            throw new NotImplementedException();
        }
    }
}
