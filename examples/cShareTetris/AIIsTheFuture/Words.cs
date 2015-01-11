using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AIIsTheFuture
{
    class Words
    {
        public static List<int> GetAWord(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11)
        {
            List<int> ls = new List<int>();
            ls.Add(a0);
            ls.Add(a1);
            ls.Add(a2);
            ls.Add(a3);
            ls.Add(a4);
            ls.Add(a5);
            ls.Add(a6);
            ls.Add(a7);
            ls.Add(a8);
            ls.Add(a9);
            ls.Add(a10);
            ls.Add(a11);
            return ls;
        }

        public static Dictionary<int, List<int>> GetWords()
        {
            Dictionary<int, List<int>> dict = new Dictionary<int, List<int>>();
            dict.Add(0, GetAWord(272, 166, 66, 338, 498, 162, 1022, 672, 1016, 168, 1016, 160));
            //dict.Add(1, GetAWord(323, 293, 276, 276, 1364, 958, 290, 290, 162, 1954, 318, 512));
            return dict;
        }


        //"272\n166\n66\n338\n498\n162\n1022\n672\n1016\n168\n1016\n160\n"   // fei  12
        //292\n168\n168\n112\n32\n508\n32\n168\n32\n1022\n32\n32\n // lai   12
        //131\n388\n148\n648\n404\n208\n144\n1022\n144\n144\n900\n192  // wo   12
        //248\n0\n1022\n80\n248\n136\n248\n0\n508\n32\n1022\n32\n + 136 + 248 // xi   14~~
        //"0\n33\n18\n1100\n644\n260\n673\n2015\n8\n4\n0\n0\n" //欢 9
        //"256\n280\n264\n329\n298\n264\n264\n266\n322\n830\n272\n128\n" //ni 12
        // 512\n512\n512\n737\n682\n740\n586\n578\n751\n1604\n514\n256\n  //zuo 11  512 ?
        //131\n388\n148\n648\n404\n208\n144\n1022\n144\n144\n900\n192  // wo   12
        //"4\n970\n578\n578\n586\n586\n578\n962\n286\n136\n0\n0\n" // de 10   
        //"140\n80\n32\n80\n80\n136\n1022\n128\n64\n32\n32\n0\n" // nv 11
        //"66\n1238\n594\n594\n990\n594\n594\n990\n594\n594\n990\n0\n" // peng 12
        // "140\n80\n32\n80\n520\n260\n252\n64\n32\n1022\n32\n0\n" // you 11
        // "63\n65\n64\n64\n1856\n1344\n1407\n1353\n1865\n127\n0\n0\n" // ba 10
    }
}
