using System;
using System.Collections.Generic;
using System.Text;

namespace Alarm
{
    interface IAkcje
    {
        void ZgasLampe();
        void ZapalLampe();

    }
    class RootClass
    {
        protected IAkcje Rodzic;
        public RootClass(IAkcje rodzic)
        {
            Rodzic = rodzic;
        }
        public virtual void Tick() { }
        // TODO Zdefiniowane zdarzenia z domyœlnymi przejœciami

        public virtual RootClass WlaczAlarm()
        {
            return this;
        }

        public virtual RootClass WylaczAlarm()
        {
            return this;
        }
        // ...
    }
    class TimeManager : RootClass
    {
        int CzasTrwaniaStanu, AktualnaIloscTykniecZegara;
        public TimeManager(IAkcje rodzic, int _CzasTrwaniaStanu)
            : base(rodzic)
        {
            CzasTrwaniaStanu = _CzasTrwaniaStanu;
            AktualnaIloscTykniecZegara = 0;
        }

        public virtual void TimeOut() { }

        public override void Tick()
        {
            // TODO Zdefiniowane metody

            AktualnaIloscTykniecZegara++;

            if (AktualnaIloscTykniecZegara >= CzasTrwaniaStanu)
            {
                AktualnaIloscTykniecZegara = 0;
                TimeOut();
            }
        }
    }

    //TODO Zdefiniowane stany
    class Off : TimeManager
    {
        public Off(IAkcje rodzic)
            : base(rodzic, 3) // Obiekt bedzie gotowy przez 3 sek
        {
            Rodzic.ZgasLampe();
        }
        //Zdefiniowane przejœcia dla danego stanu do innych stanów

        public override RootClass WlaczAlarm()
        {
            return new On(Rodzic);
        }
    }

    class On : TimeManager
    {
        private bool isOn = false;

        public On(IAkcje rodzic)
               : base(rodzic, 3)
        {
            Rodzic.ZapalLampe();
            isOn = true;
        }

        public override RootClass WylaczAlarm()
        {
            return new Off(Rodzic);
        }

        public override void TimeOut()
        {
            if (isOn == true)
            {
                Rodzic.ZgasLampe();
            }
            else
            {
                Rodzic.ZapalLampe();
            }

            isOn = !isOn;
        }
    }
}
