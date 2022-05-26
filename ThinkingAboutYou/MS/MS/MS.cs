using System;
using System.Collections.Generic;
using System.Diagnostics;
using static System.Console;

namespace MS
{
    internal class Coroutine
    {
        public static int tsclothes;

        public static void Main()
        {
            Stopwatch tssw = new Stopwatch();
            Random tsrdm = new Random();
            String tsstr = null;

            MJ mj = new MJ();
            IEnumerator<string> mjenumerator = mj.mjenumerator();

            while (true)
            {
                tssw.Reset();
                tssw.Start();

                mjenumerator.MoveNext();

                tsstr = "TS    옷 입는 중...";
                WriteLine(tsstr);
                WriteLine(mjenumerator.Current);
                while (true)
                {
                    mjenumerator.MoveNext();
                    tssw.Stop();
                    if (tssw.ElapsedMilliseconds > 3000)
                    {
                        tsstr = "TS    다 입음!";
                        WriteLine(tsstr);
                        SetCursorPosition(CursorLeft, CursorTop - 1);

                        if (mjenumerator.Current == "\nMJ    다 입음!") //MJ도 옷을 다 입었을 때 종료
                        {
                            WriteLine(mjenumerator.Current);
                            break;
                        }
                    }
                    tssw.Start();
                }
                tsclothes = tsrdm.Next(1, 6);
                tsstr = "TS    내가 입은 옷은 " + tsclothes + "번이야!";

                mjenumerator.MoveNext();
                WriteLine(tsstr);
                WriteLine(mjenumerator.Current);

                mjenumerator.MoveNext();
                if (mjenumerator.Current == tsclothes.ToString())
                {
                    tsstr = "TS    같은 옷이다!";
                    WriteLine(tsstr);
                    WriteLine("MJ    학교 가자!\n");
                    break;
                }
                else
                {
                    tsstr = "TS    아 안 맞네...";
                    WriteLine(tsstr);
                    WriteLine("MJ    아 다시 입어...\n");
                    tsstr = null;
                }
            }
        }
    }

    internal class MJ
    {
        Stopwatch mjsw = new Stopwatch();
        Random mjrdm = new Random();
        string mjstr = null;
        int mjclothes;

        public IEnumerator<string> mjenumerator()
        {
            while (true)
            {
                mjstr = "MJ    옷 입는 중...";
                mjsw.Reset();
                mjsw.Start();
                yield return mjstr;

                while (true)
                {
                    mjsw.Stop();
                    if (mjsw.ElapsedMilliseconds > 5000)
                    {
                        break;
                    }
                    mjsw.Start();
                    yield return mjstr;
                }
                mjstr = "\nMJ    다 입음!";
                yield return mjstr;

                mjclothes = mjrdm.Next(1, 6);
                mjstr = "MJ    내가 입은 옷은 " + mjclothes + "번이야!";
                yield return mjstr;

                yield return mjclothes.ToString();

                mjstr = null;
            }
        }
    }
}