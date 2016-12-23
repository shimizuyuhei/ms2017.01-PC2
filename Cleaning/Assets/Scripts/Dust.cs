using UnityEngine;
using System.Collections;

/// 敵
public class Dust : Token
{
    public int DeathCnt = 0;

    SpriteRenderer DustSprite;
    public Sprite[] DustState = new Sprite[3];

    /// 開始
    void Start()
    {
        GameMgr.Count++;

        //Debug.Log("Hello");
        DustSprite = gameObject.GetComponent<SpriteRenderer>();
    }

    /// 更新
    void Update()
    {
        if(TCP_Signal.signal == '1')
        {
            HitPoints();
            TCP_Signal.signal = 0;
        }
    }

    /// クリックされた
    public void OnMouseDown()
    {
        HitPoints();
    }

    private void HitPoints()
    {
        if (DeathCnt < 3)
        {
            DustSprite.sprite = DustState[DeathCnt];
            DeathCnt++;
            // パーティクルを生成
            for (int i = 0; i < 32; i++)
            {
                Particle.Add(X, Y);
            }
        }
        else
        {
            // パーティクルを生成
            for (int i = 0; i < 32; i++)
            {
                Particle.Add(X, Y);
            }

            /*生存数を減らす*/
            GameMgr.Count--;

            // 破棄する
            DestroyObj();
        }
    }
}