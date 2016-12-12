using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*通信宣言*/
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Text;

/*スレット*/
using System.Threading;

public class TCP_Signal : MonoBehaviour
{

    private Thread TCP_Thread;

    private StreamReader sr;
    private StreamWriter sw;

    // Use this for initialization
    void Start()
    {
        Debug.Log("TCP");

        TCP_Thread = new Thread(threadWork);
        TCP_Thread.Start();
    }

    // Update is called once per frame
    void Update()
    {

    }

    private Boolean deathflg = true;

    void OnDestroy()
    {
        deathflg = false;
    }

    private void threadWork()
    {
        /*ネットワーク設定用タスク*/
        /*ネットワークの設定*/
        /*自分のIPアドレス,ポート番号*/
        IPEndPoint ep = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 9876);

        while (deathflg)
        {
            TcpClient client = new TcpClient();

            /*サーバーに接続できたかの判定*/
            try
            {
                client.Connect(ep);     //接続の開始　Connect(繋ぐ)
                Debug.Log("接続された");

                NetworkStream ns = client.GetStream();
                sr = new StreamReader(ns);  //読み込み
                sw = new StreamWriter(ns, Encoding.UTF8);   //文字コードを指定して送信
                sw.AutoFlush = true;    //一行書き込んだら送信する

                Recive();

            }
            catch (Exception e)
            {
                Debug.Log(e.Message);   //接続できなかった場合の処理
            }

            System.Threading.Thread.Sleep(1000);
        }
    }

    private void Recive()
    {
        int[] str = new int[255];
        do
        {
            int ReadCnt = 0;
            while (0 < sr.Peek())
            {
                str[ReadCnt] = sr.Read();
                ReadCnt++;
            }
            //txtDisp.Text = str;
            if(0 < ReadCnt)
            {
                Debug.Log(str[0].ToString("x"));
            }
        } while (deathflg);
    }
}
