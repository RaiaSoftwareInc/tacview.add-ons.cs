using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using MessageBox = System.Windows.Forms.MessageBox;

namespace M2000D.carto
{
    /// <summary>
    /// Logique d'interaction pour DeleteOgcServer.xaml
    /// </summary>
    public partial class DeleteOgcServer : Window
    {
        private MainMenu mainMenu;

        public DeleteOgcServer()
        {
            InitializeComponent();
        }
        private void loadServer()
        {
            if (mainMenu != null)
            {
                foreach (KeyValuePair<string, string> ogcserver in this.mainMenu.ogcServerList)
                {
                    serverNameCombobox.Items.Add(ogcserver.Key);
                }
                serverNameCombobox.SelectedItem = this.mainMenu.selectedServer;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Delete_Click(object sender, RoutedEventArgs e)
        {
            if (mainMenu != null)
            {
                if (serverNameCombobox.SelectedItem != null)
                {
                    if (this.mainMenu.selectedServer != serverNameCombobox.Text)
                    {

                        DialogResult confirmResult = MessageBox.Show("Are you sure to delete this server ??", "Confirm Delete!!", MessageBoxButtons.YesNo);
                        if (confirmResult == System.Windows.Forms.DialogResult.Yes)
                        {
                            this.mainMenu.ogcServerList.Remove(serverNameCombobox.Text);
                            this.mainMenu.settingsSaveServerList();
                        }
                    }
                    else
                    {
                        MessageBox.Show("You can't delete the current selected server.");
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
    }
}
