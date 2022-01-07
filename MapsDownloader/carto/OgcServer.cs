using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace M2000D.carto
{
    class OgcServer
    {
        public bool selected { set; get; }
        public string name { set; get; }
        public string url { set; get; }

        public OgcServer(bool selected, string name, string url)
        {
            this.selected = selected;
            this.name = name;
            this.url = url;
        }

        public override bool Equals(object obj)
        {
            return obj is OgcServer server &&
                   selected == server.selected &&
                   name == server.name &&
                   url == server.url;
        }

        public override int GetHashCode()
        {
            int hashCode = 1613126824;
            hashCode = hashCode * -1521134295 + selected.GetHashCode();
            hashCode = hashCode * -1521134295 + EqualityComparer<string>.Default.GetHashCode(name);
            hashCode = hashCode * -1521134295 + EqualityComparer<string>.Default.GetHashCode(url);
            return hashCode;
        }
    }
}
