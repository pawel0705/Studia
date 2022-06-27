using System;
using System.Collections.Generic;
using System.Text;

namespace menu
{
    interface IAkcje
    {
        void WejscieDoGlownegoMenu();
        void Wyjscie();
        void WejscieDoOpcje();
        void WejscieDoZaawansowane();
        void WejscieDoStandardowe();
        void WejscieDoStart();

    }
    class RootClass
    {
        protected IAkcje Rodzic;
        public RootClass(IAkcje rodzic)
        {
            Rodzic = rodzic;
        }
        // TODO Zdefiniowane zdarzenia z domyœlnymi przejœciami
        public virtual RootClass Zdarzenie1() { return this; }

        public virtual RootClass Zdarzenie2() { return this; }
        // ...

        public virtual RootClass Zdarzenie3() {return this;}
    }
    //Zdefiniowane stany
    class GlowneMenu : RootClass
    {
        public GlowneMenu(IAkcje rodzic) : base(rodzic) 
        {
            //Zdefiniowane Akcje
            Rodzic.WejscieDoGlownegoMenu();
        }
        //Zdefiniowane przejœcia dla danego stanu do innych stanów
        public override RootClass Zdarzenie3()
        {
            Rodzic.Wyjscie();
            return this;
        }

        public override RootClass Zdarzenie1()
        {
            return new Start(Rodzic);
        }

        public override RootClass Zdarzenie2()
        {
            return new Ustawienia(Rodzic);
        }
    }

    class GlowneMenuChild : GlowneMenu
    {
        public GlowneMenuChild(IAkcje rodzic) : base(rodzic)
        {
            Rodzic.WejscieDoGlownegoMenu();
        }

        public override RootClass Zdarzenie3()
        {
            return new GlowneMenu(Rodzic);
        }
    }


    class Start : GlowneMenuChild
    {
        public Start(IAkcje rodzic) : base(rodzic)
        {
            Rodzic.WejscieDoStart();
        }
    }

    class Ustawienia : GlowneMenuChild
    {
        public Ustawienia(IAkcje rodzic) : base(rodzic)
        {
            Rodzic.WejscieDoOpcje();
        }

        public override RootClass Zdarzenie1()
        {
            return new Standardowe(Rodzic);
        }

        public override RootClass Zdarzenie2()
        {
            return new Zaawansowane(Rodzic);
        }
    }


    class UstawieniaChild : Ustawienia
    {
        public UstawieniaChild(IAkcje rodzic) : base(rodzic)
        {
            Rodzic.WejscieDoOpcje();
        }

        public override RootClass Zdarzenie3()
        {
            return new Ustawienia(Rodzic);
        }
    }

    class Standardowe : UstawieniaChild
    {
        public Standardowe(IAkcje rodzic) : base(rodzic)
        {
            Rodzic.WejscieDoStandardowe();
        }
    }

    class Zaawansowane : UstawieniaChild
    {
        public Zaawansowane(IAkcje rodzic) : base(rodzic)
        {
            Rodzic.WejscieDoZaawansowane();
        }
    }
}
