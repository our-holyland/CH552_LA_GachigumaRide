/*
 *  ★ポケモンレジェンズアルセウス　ガチグマライドで色々掘ろう＠天冠の山麓 山頂ベース★
 *  天冠の山麓の山頂ベースでArduinoを挿すとスタート。
 *  ライドポケモンは、「ガチグマ」にカーソルがあっている状態で使うこと！（重要）
 *
 *
 * 実測値で、12時間放置で242ループ。下記が手に入りました。
 * ・ピートブロック：13個
 * ・クスリソウ：242個
 * ・ごりごりミネラル：404個
 * ・スイートトリュフ：81個
 * ・どろだんご：260個
 * ・ほしのかけら：20個
 * ・つきのいし：12個
 * ・そらいろたまいし：200個
 * ・たいようのいし：7個
 * ・くろのきせき：9個
 *
 *  設定
 *  ・はなしのはやさ：はやい
 *
 *  (c) 2022 ますたーの忘備録
 *  https://tangential-star.hatenablog.jp/
*/

#include <CH55xSwitchControl.h>

#define HOLDTIME (95)     // 1回のキー入力の長押し時間

// ★修正ここから★-----------------

// 【天冠の山麓】マップでXを押したときに「山頂ベース」が上から何番目か？（山麓ベース=0・山中=1・山頂=2・迎月の戦場=3・やめる）
const int SANROKU = 0; // 山麓ベース
const int SANCHU  = 1; // 山中ベース
const int SANCHO  = 2; // 山頂ベース
const int GEIGETSU= 3; // 迎月の戦場

// 【コトブキムラ】マップでXを押したときに「表門前」が何番目か？
const int HOMBU    = 0; // 本部前
const int OMOTEMON = 1; // 表門前
const int YAGAI    = 2; // 野外訓練場
const int NOUJO    = 3; // 農場前
const int KUNRENJO = 4; // 訓練場前

// 【入り口】マップでカーソルを外してから「↓」キーで「天冠の山麓」が何番目か？
const int KOTOBUKI = 1; // コトブキムラ
const int KOKUYO   = 2; // 黒曜の原野
const int GUREN    = 3; // 紅蓮の湿地
const int GUNJO    = 4; // 群青の海岸
const int TENGAN   = 5; // 天冠の山麓
const int JUMPAKU  = 6; // 純白の糖度
const int INISHIE  = 7; // 古の隠れ里

// 角度データcos
const long cos_data[] = {
  6553600L, // cos(0)*65536*100
  6552602L, // cos(1)*65536*100
  6549608L, // cos(2)*65536*100
  6544619L, // cos(3)*65536*100
  6537636L, // cos(4)*65536*100
  6528662L, // cos(5)*65536*100
  6517699L, // cos(6)*65536*100
  6504750L, // cos(7)*65536*100
  6489821L, // cos(8)*65536*100
  6472914L, // cos(9)*65536*100
  6454036L, // cos(10)*65536*100
  6433192L, // cos(11)*65536*100
  6410388L, // cos(12)*65536*100
  6385632L, // cos(13)*65536*100
  6358930L, // cos(14)*65536*100
  6330291L, // cos(15)*65536*100
  6299725L, // cos(16)*65536*100
  6267239L, // cos(17)*65536*100
  6232844L, // cos(18)*65536*100
  6196551L, // cos(19)*65536*100
  6158370L, // cos(20)*65536*100
  6118313L, // cos(21)*65536*100
  6076392L, // cos(22)*65536*100
  6032621L, // cos(23)*65536*100
  5987012L, // cos(24)*65536*100
  5939579L, // cos(25)*65536*100
  5890337L, // cos(26)*65536*100
  5839300L, // cos(27)*65536*100
  5786485L, // cos(28)*65536*100
  5731908L, // cos(29)*65536*100
  5675584L, // cos(30)*65536*100
  5617532L, // cos(31)*65536*100
  5557768L, // cos(32)*65536*100
  5496311L, // cos(33)*65536*100
  5433181L, // cos(34)*65536*100
  5368395L, // cos(35)*65536*100
  5301974L, // cos(36)*65536*100
  5233938L, // cos(37)*65536*100
  5164307L, // cos(38)*65536*100
  5093104L, // cos(39)*65536*100
  5020349L, // cos(40)*65536*100
  4946065L, // cos(41)*65536*100
  4870274L, // cos(42)*65536*100
  4793000L, // cos(43)*65536*100
  4714265L, // cos(44)*65536*100
  4634095L, // cos(45)*65536*100
  4552513L, // cos(46)*65536*100
  4469544L, // cos(47)*65536*100
  4385214L, // cos(48)*65536*100
  4299548L, // cos(49)*65536*100
  4212573L, // cos(50)*65536*100
  4124314L, // cos(51)*65536*100
  4034799L, // cos(52)*65536*100
  3944055L, // cos(53)*65536*100
  3852109L, // cos(54)*65536*100
  3758991L, // cos(55)*65536*100
  3664727L, // cos(56)*65536*100
  3569346L, // cos(57)*65536*100
  3472879L, // cos(58)*65536*100
  3375354L, // cos(59)*65536*100
  3276800L, // cos(60)*65536*100
  3177248L, // cos(61)*65536*100
  3076729L, // cos(62)*65536*100
  2975272L, // cos(63)*65536*100
  2872909L, // cos(64)*65536*100
  2769671L, // cos(65)*65536*100
  2665589L, // cos(66)*65536*100
  2560696L, // cos(67)*65536*100
  2455022L, // cos(68)*65536*100
  2348600L, // cos(69)*65536*100
  2241463L, // cos(70)*65536*100
  2133643L, // cos(71)*65536*100
  2025174L, // cos(72)*65536*100
  1916087L, // cos(73)*65536*100
  1806417L, // cos(74)*65536*100
  1696196L, // cos(75)*65536*100
  1585459L, // cos(76)*65536*100
  1474239L, // cos(77)*65536*100
  1362570L, // cos(78)*65536*100
  1250486L, // cos(79)*65536*100
  1138021L, // cos(80)*65536*100
  1025209L, // cos(81)*65536*100
  912085L, // cos(82)*65536*100
  798683L, // cos(83)*65536*100
  685038L, // cos(84)*65536*100
  571184L, // cos(85)*65536*100
  457156L, // cos(86)*65536*100
  342989L, // cos(87)*65536*100
  228717L, // cos(88)*65536*100
  114376L, // cos(89)*65536*100
  0L, // cos(90)*65536*100
};

// ★修正ここまで★-----------------

bool isFirstLoop = true;

void PushRL(int delay_time_ms);
int PushKey(char* keyname, int holdtime, int delaytime);
void TiltLeftStick(int direction_deg, int power, unsigned long int holdtime, unsigned long int delaytime);
void Die(void);

void JumpTo(int destination){
  // destination: cursor where you want to go in map (ArceusPhone).
  int i=0;
  PushKey("-", HOLDTIME, 1200);
  PushKey("X", HOLDTIME, 1000);
  for(i=0; i<destination; i++)PushKey("down", HOLDTIME, 250);
  PushKey("A", HOLDTIME, 3300);
  return;
}
void Turn(int degree){
  TiltLeftStick( degree, 30, 140, 300);
  PushKey("ZL", HOLDTIME, 1000);
  return;
}
void Dash(unsigned long msecond){
  TiltLeftStick( 0, 100, msecond, 300);
  return;
}
void Dash_interruptA(unsigned long msecond, unsigned long msecond_interruptA){
  TiltLeftStick( 0, 100, 0, msecond_interruptA); // 傾けて
  PushKey("A", HOLDTIME, (msecond - msecond_interruptA));
  TiltLeftStick( 0, 0, 0, 300); // 傾きをもどす
  return;
}

void PokeThrow(int delaytime, int holdingballtime){
  // ボールを構えて
  pressButton(BUTTON_ZR); delay(holdingballtime);
  // ボールを投げる
  releaseButton(BUTTON_ZR); delay(delaytime);
  return;
}
void RidePoke(void){
  PushKey("+", HOLDTIME, 1200);
  return;
}

void Dig(void){
  PushKey("Y", HOLDTIME, 400);
  return;
}

void DashBack(void){ // call this function after Dig()
  TiltLeftStick( 180, 100, 3500, 300);
  PushKey("B", HOLDTIME, 300);
  return;
}

void BackToJubilifeVillage(void){
  // 山頂ベースに飛んで
  JumpTo(SANCHO);

  // 博士に話しかける
  TiltLeftStick( 48, 100, 900, 300);
  PushKey("A", HOLDTIME, 900);    // 報告できることは 特にないようですね ▼
  PushKey("A", HOLDTIME, 700);    // これから どうするのですか？ ▼
  PushKey("A", HOLDTIME, 700);    // →調査を続ける
  PushKey("down", HOLDTIME, 350); // →ムラに戻る
  PushKey("A", HOLDTIME, 1200);   // では コトブキムラに戻りましょう 大丈夫です 警備隊も一緒ですよ ▼
  PushKey("A", HOLDTIME, 12000);  // 移動中…
  return;
}

void GotoCoronetHighlands(void){
  int i=0;
  // 表門前に飛んで
  JumpTo(OMOTEMON);

  // デンスケに話しかける
  TiltLeftStick( 23, 100, 2000, 500); // 外に出るのか？気をつけてな or ポケモン大大大発生の 報告があったらしいぞ！ 気をつけてな
  PushKey("A", HOLDTIME, 1200); // マップを開く
  if(isFirstLoop){
    TiltLeftStick( 0, 100, 1700, 500); // カーソルを外にはずして
    for(i=0; i<TENGAN; i++)PushKey("down", HOLDTIME, 250); // 「天冠の山麓」にカーソルをあわせる
  }
  PushKey("A", HOLDTIME, 600); // 「天冠の山麓」を選択

  for(i=0; i<SANCHO ; i++)PushKey("down", HOLDTIME, 250); // 「山頂ベース」を選択
  PushKey("A", HOLDTIME, 12000); // 移動中…

  return;
}

void setup() {
  // USBコントローラーの初期化
  USBInit();

  for(int i=0; i < 5 ; i++)PushKey("B", HOLDTIME, 700);
}

void loop() {

  // 振り返ってガチグマライド掘り起こしポイントへ

  // 超左バージョン
  if(isFirstLoop)JumpTo(SANCHO);
  //Turn(169);
  Turn(168);
  Dash_interruptA(15800, 9630); // クスリソウを拾う
  RidePoke();
  Dig();
  DashBack();

  // 左バージョン
  JumpTo(SANCHO);
  Turn(177);
  Dash(16900);
  RidePoke();
  Dig();
  TiltLeftStick( 200, 100, 1600, 300); // ここにもずれることがある
  Dig();
  DashBack();

  // 真ん中バージョン
  JumpTo(SANCHO);
  Turn(189);
  //Dash(18.4, 16.64); // ごりごりミネラル を拾う
  Dash_interruptA(18000, 16100); // ごりごりミネラル を拾う
  RidePoke();
  Dig();
  DashBack();

  // 右バージョン
  JumpTo(SANCHO);
  Turn(201);
  Dash(15200);
  RidePoke();
  Dig();
  TiltLeftStick( 180, 100, 13000, 2800); // 一番右は、まれにドータクン・ドーミラーに索敵されるので走って基地側へ

  // Die(); // debug

  // コトブキムラに戻る
  BackToJubilifeVillage();

  // 天冠の山麓（山頂ベース）に戻る
  GotoCoronetHighlands();

  isFirstLoop = false;
}

void PushRL(int delay_time_ms){
  pressButton(BUTTON_R);
  pressButton(BUTTON_L);
  delay(HOLDTIME);
  releaseButton(BUTTON_R);
  releaseButton(BUTTON_L);
  delay(delay_time_ms);
  return;
}
int PushKey(char* keyname, int holdtime, int delaytime){
  // ホームボタン・方向キーはRight, Left, Up, Down, Homeなど2文字以上で入力。
  // その他ボタン入力は1文字（A,B,X,Y,R,L,+,-）ZR・ZLにも対応
  // 同時押しは非対応

  if(strlen(keyname)==1){
    switch(keyname[0]){
      case 'A': case 'a': // A
        pressButton(BUTTON_A); delay(holdtime);
        if(holdtime>0)releaseButton(BUTTON_A); delay(delaytime);
      break;
      case 'B': case 'b': // B
        pressButton(BUTTON_B); delay(holdtime);
        if(holdtime>0)releaseButton(BUTTON_B); delay(delaytime);
      break;
      case 'X': case 'x': // X
        pressButton(BUTTON_X); delay(holdtime);
        if(holdtime>0)releaseButton(BUTTON_X); delay(delaytime);
      break;
      case 'Y': case 'y': // Y
        pressButton(BUTTON_Y); delay(holdtime);
        if(holdtime>0)releaseButton(BUTTON_Y); delay(delaytime);
      break;
      case 'L': case 'l': // L
        pressButton(BUTTON_L); delay(holdtime);
        if(holdtime>0)releaseButton(BUTTON_L); delay(delaytime);
      break;
      case 'R': case 'r': // R
        pressButton(BUTTON_R); delay(holdtime);
        if(holdtime>0)releaseButton(BUTTON_R); delay(delaytime);
      break;
      case 'H': case 'h': // Home
        pressButton(BUTTON_HOME); delay(holdtime);
        if(holdtime>0)releaseButton(BUTTON_HOME); delay(delaytime);
      break;
      case '+': case 'p': case 'P': // Plus
       pressButton(BUTTON_PLUS); delay(holdtime);
        if(holdtime>0)releaseButton(BUTTON_PLUS); delay(delaytime);
      break;
      case '-': case 'm': case 'M': // Minus
        pressButton(BUTTON_MINUS); delay(holdtime);
        if(holdtime>0)releaseButton(BUTTON_MINUS); delay(delaytime);
      break;
      default:
      break;
    }
  }else if(strlen(keyname)>=2){
    switch(keyname[0]){
      case 'z': case 'Z': // ZR/ZL
        if(keyname[1]=='R'||keyname[1]=='r'){
          pressButton(BUTTON_ZR); delay(holdtime);
          if(holdtime>0)releaseButton(BUTTON_ZR); delay(delaytime);
        }
        if(keyname[1]=='L'||keyname[1]=='l'){
          pressButton(BUTTON_ZL); delay(holdtime);
          if(holdtime>0)releaseButton(BUTTON_ZL); delay(delaytime);
        }
      break;
      case 'r': case 'R': // right
        pressHatButton(HAT_RIGHT); delay(holdtime);
        if(holdtime>0)releaseHatButton(); delay(delaytime);
      break;
      case 'l': case 'L': // left
        pressHatButton(HAT_LEFT); delay(holdtime);
        if(holdtime>0)releaseHatButton(); delay(delaytime);
      break;
      case 'u': case 'U': // up
        pressHatButton(HAT_UP); delay(holdtime);
        if(holdtime>0)releaseHatButton(); delay(delaytime);
      break;
      case 'd': case 'D': // down
        pressHatButton(HAT_DOWN); delay(holdtime);
        if(holdtime>0)releaseHatButton(); delay(delaytime);
      break;
      case 'H': case 'h': // Home
        pressButton(BUTTON_HOME); delay(holdtime);
        if(holdtime>0)releaseButton(BUTTON_HOME); delay(delaytime);
      default:
      break;
    }
  }else{
    return -1;
  }
  return strlen(keyname);
}

//direction_deg:上0deg、右90deg、下180deg、左270deg
//power:スティックを倒す強さ(0~100)
//holdtime:スティックを倒し続ける時間(ms)
//delaytime:スティックを話した後の時間(ms)
void TiltLeftStick(int direction_deg, int power, unsigned long int holdtime, unsigned long int delaytime){
  int deg, cos_s,sin_s;
  int x, y;

  deg = direction_deg % 360;
  if(deg < 90){
    cos_s = 1;
    sin_s = 1;
  }else if(deg < 180){
    deg  = 180 - deg;
    cos_s = -1;
    sin_s = 1;
  }else if(deg < 270){
    deg = deg - 180;
    cos_s = -1;
    sin_s = -1;
  }else{
    deg  = 360 - deg;
    cos_s = 1;
    sin_s = -1;
  }
  x = (long)sin_s * cos_data[90-deg] * power / 6553600L;
  y = -(long)cos_s * cos_data[deg] * power / 6553600L;
  if(x >= 100) x=100; if(x <= -100) x=-100;
  if(y >= 100) y=100; if(y <= -100) y=-100;

  setStickTiltRatio(x,y,0,0);
  if(holdtime> 0){ // holdtime=0のときは押しっぱなし。
    delay(holdtime);
    setStickTiltRatio(0,0,0,0); // 傾きを直す
  }
  if(delaytime>0) delay(delaytime);
  return;
}

void Die(void){
  for(;;)delay(100);
}
