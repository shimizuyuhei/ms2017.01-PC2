using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class House : Token
{
    public int DeathCnt = 0;

    SpriteRenderer HouseSprite;
    public Sprite[] HouseState = new Sprite[3];

    /// 開始
    void Start()
    {
        //Debug.Log("Hello");
        HouseSprite = gameObject.GetComponent<SpriteRenderer>();

    }

    /// 更新
    void Update()
    {

    }

    /// クリックされた
    public void OnMouseDown()
    {
        if (DeathCnt < 3)
        {
            HouseSprite.sprite = HouseState[DeathCnt];
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

            // 破棄する
            DestroyObj();
        }
    }
}
