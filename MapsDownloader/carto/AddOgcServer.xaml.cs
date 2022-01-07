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
    /// Logique d'interaction pour AddOgcServer.xaml
    /// </summary>
    public partial class AddOgcServer : Window
    {
        private MainMenu mainMenu;

        public AddOgcServer()
        {
            //this.mainMenu = mainMenu;
            InitializeComponent();
        }

        private void Ok_Click(object sender, RoutedEventArgs e)
        {
            this.mainMenu.addServer(NameTextBox.Text, urlTextBox.Text);
            this.Close();
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        internal void setParent(MainMenu mainMenu)
        {
            this.mainMenu = mainMenu;
        }

    }
}
