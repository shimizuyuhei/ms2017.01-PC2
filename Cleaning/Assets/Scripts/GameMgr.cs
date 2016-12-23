﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameMgr : MonoBehaviour {

    /*エネミー数*/
    public static int Count = 0;

    void OnGUI()
    {
        if (Count == 0)
        {
            // 敵が全滅した
            // フォントサイズ設定
            Util.SetFontSize(32);
            // 中央揃え
            Util.SetFontAlignment(TextAnchor.MiddleCenter);

            // フォントの位置
            float w = 128; // 幅
            float h = 32; // 高さ
            float px = Screen.width / 2 - w / 2;
            float py = Screen.height / 2 - h / 2;

            // フォント描画
            Util.GUILabel(px, py, w, h, "Game Clear!");

            // ※ここから追加
            // ボタンは少し下にずらす
            py += 60;
            if (GUI.Button(new Rect(px, py, w, h), "Back to Title") || TCP_Signal.signal == 0x62)
            {
                // タイトル画面にもどる
                Application.LoadLevel("Title");
                TCP_Signal.signal = 0;
            }
        }
    }
}
