using System;
using System.Collections.Generic;
using System.Text;

namespace Winda
{
    interface IAkcje
    {
        void DotarcieNaGore();
        void DotarcieNaDol();
        void JazdaNaGore();
        void JazdaNaDol();
    }
    class RootClass
    {
        protected IAkcje Rodzic;
        public RootClass(IAkcje rodzic)
        {
            Rodzic = rodzic;
        }
        // TODO Zdefiniowane zdarzenia i ich domyœlne zachowanie

        public virtual RootClass WcisnieciePrzycisku()
        {
            return this;
        }

        public virtual RootClass DojechanieDoPietra()
        {
            return this;
        }
    }

    class Dol : RootClass
    {
        public Dol(IAkcje rodzic)
            : base(rodzic) 
        {
            Rodzic.DotarcieNaDol();
        }
        //TODO Zdefiniowane przejœcia dla danego stanu do innych stanów

        public override RootClass WcisnieciePrzycisku()
        {
            return new PoruszanieWGore(Rodzic);
        }
    }

    //TODO Zdefiniowane dodatkowych klas - stanow
    class Gora : RootClass
    {
        public Gora(IAkcje rodzic)
            : base(rodzic)
        {
            Rodzic.DotarcieNaGore();
        }

        public override RootClass WcisnieciePrzycisku()
        {
            return new PoruszanieWDol(Rodzic);
        }
    }

    class PoruszanieWGore : RootClass
    {
        public PoruszanieWGore(IAkcje rodzic)
            : base(rodzic)
        {
            Rodzic.JazdaNaGore();
        }

        public override RootClass DojechanieDoPietra()
        {
            return new Gora(Rodzic);
        }
    }

    class PoruszanieWDol : RootClass
    {
        public PoruszanieWDol(IAkcje rodzic)
            : base(rodzic)
        {
            Rodzic.JazdaNaDol();
        }

        public override RootClass DojechanieDoPietra()
        {
            return new Dol(Rodzic);
        }
    }
}
