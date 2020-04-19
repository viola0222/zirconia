
## 概要
___

「zilconia」はマイクロマウスのチャンピオンが製作したオープンソースのマイクロマウスです。 
   
詳しい紹介は[製作者のブログ](http://matsui-mouse.blogspot.com/2018/07/zirconia.html)にお任せするとして、私はそのサンプルコードを書いています。  
ハードウェアの設計データは[ここ](http://matsui-mouse.blogspot.com/2019/04/zirconia.html)にありますので、これからマイクロマウスを製作しようと考えている人たちの助けになれば幸甚です。  
  
![zilconia](https://bitbucket.org/kohiro/zirconia_sample/src/master/zilconia.jpg, 'zilconia')

## 機能
___
 
各種インターフェースやセンサーの動作確認  

- マイコン各種機能(STM32F413)
- LED
- プッシュスイッチ
- モータ
- エンコーダ(MA300)
- IMU(ICM20648)
- IRセンサ
  
機能の詳細についてはソフトマニュアルとサンプルコードのindex.hを参照して下さい。
 
## 動作環境
___
 
- 統合開発環境
    - STM32CubeIDE
    - Version :  1.3.0
    - URL : https://www.st.com/ja/development-tools/stm32cubeide.html

- フラッシュライター
	- STM32CubeProgrammer
	- Version : 2.3.0
 	- URL : https://www.st.com/ja/development-tools/stm32cubeprog.html

※ Versionにはサンプルプログラムを開発したときのものを記載してあります。  
　　基本的には最新版をインストールすべきだと思いますが、  
　　サンプルプログラムが動かない等の不具合がありましたら参考にして下さい。

## 構成
___
 
- hardware
    - 回路図やガーバーデータ、部品リストなどハードウェアデータ
- software
    - CubeMXで自動生成したソフトと本サンプルプログラム
    - Incフォルダ内のIndex.hにサンプルプログラムの使い方が記載されています
    - Srcフォルダ内にmain.cなどのサンプルプログラムが入っています
- ハードマニュアル
    - ハードウェアの作り方や構成について記載されています
- ソフトマニュアル
    - サンプルプログラムの導入や使い方について記載されています
 
## その他
 ___

__本サンプルコードではマイクロマウスとして迷路を完走させることはできません。__  
本サンプルコードの目的は、製作したハードウェアの動作確認であり、その副産物として、マイクロマウスとして使いやすいデバイスドライバを書いたつもりです。  
  
あくまでもzilconiaは動くハードウェアを用意しただけなので、ソフトウェアは自力で頑張れる人向けです。電子工作やプログラミングのガチ初心者にはオススメしません。  
電子工作や組み込みプログラム入門として、マイクロマウスを始める場合には(株)アールティより販売されている学習キット[Pi:Co Classic3](https://www.rt-net.jp/products/pico3)や[HM-StarterKit](https://www.rt-net.jp/products/hm-star-k)がオススメです。
 
## 作者
___
 
[コヒロ@Savant013](https://twitter.com/Savant013)
 