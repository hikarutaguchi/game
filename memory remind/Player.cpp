#include <algorithm>
#include "DxLib.h"
#include "SceneMng.h"
#include "Player.h"
#include "Game_ctr.h"
#include "Bomb.h"

#define lpScene SceneMng::GetInstance()
#define RE_START_TIME (120U) //Uをつけるとunsiged int型になる

Player::Player(VECTOR2 setupPos ,VECTOR2 drawOffset) :Obj(drawOffset)
{
	speed = 2;

	fireLength = 2;

	int Pad[4];
	for (int i = 0; i < GetJoypadNum(); i++)
	{
		for (int j = 0; j < 28; j++)
		{
			Pad[i] = GetJoypadInputState(DX_INPUT_PAD1 + i);
		}
	}
					//　MAIN		
	keyTableID = { PAD_INPUT_DOWN,	// 下方向
				   PAD_INPUT_LEFT,	// 左方向
				   PAD_INPUT_RIGHT,	// 右方向
				   PAD_INPUT_UP	// 上方向
	};	
					// MAIN
	posTbl = { &pos.y,	&pos.x,  // 下
			   &pos.x,	&pos.y,  // 左
			   &pos.x,	&pos.y,  // 右
			   &pos.y,  &pos.x	 // 上 
	};
				 //MAIN			
	speedTbl = { PLAYER_DEF_SPEED,			// 下
				-PLAYER_DEF_SPEED,			// 左
			   	 PLAYER_DEF_SPEED,			// 右
				-PLAYER_DEF_SPEED			// 上
	};
				//MAIN	   OPP			SUB1		SUB2
	dirTbl = {  DIR_DOWN,  DIR_UP,		 DIR_LEFT,	DIR_RIGHT,		// 下(左,右)
				DIR_LEFT,  DIR_RIGHT,	 DIR_DOWN,	DIR_UP,		    // 左(下,上)
				DIR_RIGHT, DIR_LEFT,	 DIR_DOWN,	DIR_UP,			// 右(下,上)
				DIR_UP,    DIR_DOWN,	 DIR_LEFT,	DIR_RIGHT,		// 上(左,右)
	};

	mapMove = {
		true,	// MAP_ID_CUR	
		true,	// MAP_ID_FLOOR1
		true,	// MAP_ID_FLOOR2
		true,	// MAP_ID_BOMB
		true,	// MAP_ID_NON
		false,	// MAP_ID_WALL1
		false,	// MAP_ID_WALL2
		false,	// MAP_ID_BLOCK		
		true,	// ITEM_BOMB,
		true,	// ITEM_FIRE,
		true,	// ITEM_SPEED,
		true,	// ITEM_WALL_PASS,
		//true,	// ITEM_CTL,		// 起爆ｺﾝﾄﾛｰﾙ
		//true,	// ITEM_BOMB_THROW,	// 爆弾投げ
		//true,	// ITEM_FIRE_GUARD,	// 炎ｶﾞｰﾄﾞ
		//true,	// ITEM_RANDOM,		// ｱｲﾃﾑﾗﾝﾀﾞﾑ出現
	};

	Init("image/slimes.png", VECTOR2(64, 100), VECTOR2(4, 4), setupPos);
	InitAnim();
	afterkeyFlag = false;
	reStartCnt = 0U;
	fireGuardFlag = 0U;


}

Player::Player()
{
	life = PLAYER_LIFE;
}


Player::~Player()
{

}

int Player::Life()
{
	if (count > 120)
	{
		life -= 1;
		count = 0;
	}
	count++;
	return life;
}

bool Player::InitAnim(void)
{
	AddAnim("停止", 0, 0, 4, 15 ,true);
	AddAnim("移動", 0, 0, 4, 20 ,true);
	AddAnim("死亡", 4, 0, 4, 8, false);
	return true;
}

#include <functional>

void Player::SetMove(weekListObj objList, const Game_ctr & controller)
{
	//auto &keyTbl	= controller.GetCtr(KEY_TYPE_NOW);			//autoの場合実体を作るので書き換えが可能
	//auto &keyTblOld = controller.GetCtr(KEY_TYPE_OLD);

	auto &chipSize  = lpMapCtl.GetChipSize().x;


	if (GetAnim() == "死亡")	//死亡アニメ再生中
	{
		if (animEndFlag)		//ｱﾆﾒ終わったかﾌﾗｸﾞ
		{
			//ここで残機を減らしたりする
			SetAnim("停止");
			reStartCnt = RE_START_TIME;
		}
	}
	////炎とプレイヤーの判定
	//if (!fireGuardFlag)
	//{
	//	if (lpMapCtl.GetFireMapData(pos))	//炎があったら死亡
	//	{
	//		if (DethProcess())	//死亡処理したら返す
	//		{
	//			return;
	//		}
	//	}
	//}
	reStartCnt -= (reStartCnt > 0);		// reStartCnt > 0は真偽真の場合１引かれる
	visible = true;
	if ((reStartCnt / 5) % 2)	//3ﾌﾚｰﾑに一回false
	{
		visible = false;
	}

	//if ((keyTbl[KEY_INPUT_SPACE]) & (~keyTblOld[KEY_INPUT_SPACE]))
	//{
	//	AddObjList()(objList, std::make_unique<Bomb>( ((pos / chipSize) * chipSize), fireLength , lpSceneMng.GetDrawOffset() + VECTOR2( 0,-5 )) );	//fireで長さを受け取る
	//}


	//中身を分かりやすくするためにswitchを使う
	auto sidePos = [&](DIR dir,VECTOR2 pos,int speed, SIDE_CHECK sideFlg) {
		VECTOR2 side;	//配列にして初期化ﾘｽﾄにする
		switch (dir)
		{
		case DIR_LEFT:
			side = { (- (sideFlg^1) + speed), 0 };
			break;
		case DIR_RIGHT:
			//ﾁｯﾌﾟｻｲｽﾞの1つ内側なので-1してあげる,-2だと2つ後ろ側なので意味がない
			side = { (chipSize - sideFlg) + 2, 0 };
			break;
		case DIR_UP:
			side = { 0, -(sideFlg^1) + speed };
			break;
		case DIR_DOWN:
			side = { 0, ((chipSize - sideFlg) + speed) };
			break;
		default:
			break;
		}
		return pos + side;
	};
	//移動ﾁｪｯｸﾗﾑﾀﾞ
	auto CheckMove_Bomb = [&]() {
		bool rtnFlag = false;
		//①
		sharedObjList tmpList = (*objList.lock());	//中身だけ欲しいならｱｽﾀﾘｽｸ、外側が欲しいならそのまま	これでlistをｺﾋﾟｰ
		//今回は条件で消したいのでremove_if
		tmpList.remove_if([](sharedObj &obj_bomb) {return (!obj_bomb->CheckObjType(OBJ_BOMB)); });
		//当たり判定
		for (auto &bomb : tmpList)	//bombを取り出す
		{
			//比較結果返り値をrtnFlagに保存、保存する際にor代入
			rtnFlag |= (sidePos(dir, pos, 0,IN_SIDE) == sidePos(dirTbl[dir][DIR_TBL_OPP], bomb->GetPos(), 0,OUT_SIDE));
		}
		return !rtnFlag;
	};

	auto move = [&,dir = Player::dir](DIR_TBL_ID id) {		//配列にｱｸｾｽする際の引数が違うのでidにする,ｺﾋﾟｰされた前のplayerのdir
		//if (keyTbl[keyTableID[dirTbl[dir][id]]])
		//if (keyTableID[dirTbl[dir][id]])
		{
			//方向のｾｯﾄ
			Player::dir = dirTbl[dir][id];
   			//動いていいか処理
			if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Player::dir,pos,speedTbl[Player::dir],IN_SIDE))) ])	//IN_SIDEで１を渡したい
			{
				//移動不可のｵﾌﾞｼﾞｪｸﾄが隣にあった場合は処理しない
				return false;
			}
			//方向のｾｯﾄの上に書くと向きを引数として渡す必要があるので、方向のｾｯﾄの後にする
			//移動の向きをｾｯﾄはしていてほしいので、方向のｾｯﾄの後に書く
			//爆弾との当たり判定
			if ( !CheckMove_Bomb() )		//上とifの中身が同じなのでor条件で括ることもできる。
			{
				//爆弾が隣接していた場合
				return false;
			}
			//補正処理
			if ( (*posTbl[Player::dir][TBL_SUB]) % chipSize)
			{
				( *posTbl[Player::dir][TBL_SUB] ) = ( ((*posTbl[Player::dir][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
			}
			//移動処理
			( *posTbl[Player::dir][TBL_MAIN] ) += speedTbl[Player::dir];
			_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
			return true;
		}
		return false;
	};

	if (!(move( (DIR_TBL_ID)(DIR_TBL_SUB1 - (afterkeyFlag<< 1)) ) || move( (DIR_TBL_ID)(DIR_TBL_SUB2 - (afterkeyFlag<< 1))) ))	//subを優先ﾁｪｯｸ
	{
		afterkeyFlag = false;
		//移動していない場合
		if (!(move( (DIR_TBL_ID)(DIR_TBL_MAIN + (afterkeyFlag << 1)) ) || move( (DIR_TBL_ID)(DIR_TBL_OPP + (afterkeyFlag << 1))) ))	//こちでも移動しなかったら停止
		{
			SetAnim("停止");
			return;
		}
	}
	else
	{
		//subｷｰの入力があったらflagが立つ
		//afterkeyFlag  = keyTbl[ keyTableID [ dirTbl[dir][DIR_TBL_SUB1]] ];
		//afterkeyFlag |= static_cast<bool>(keyTbl[ keyTableID [ dirTbl[dir][DIR_TBL_SUB2]] ]);
		afterkeyFlag ^= (int)(GetAnim() == "停止"); 
	}
	SetAnim("移動");
}

bool Player::CheckObjType(OBJ_TYPE type)
{
	//うけっとた情報が同じなら真ちがったら偽
	return (type == OBJ_PLAYER);
}

bool Player::DethProcess()
{
	if (reStartCnt)
	{
		return false;
	}
	dir = DIR_DOWN;
	SetAnim("死亡");
	fireGuardFlag = 0U;
	return true;
}

void Player::GetItem(void)
{
	//if ((pos % lpMapCtl.GetChipSize()) != VECTOR2(0, 0))		//升目ﾋﾟｯﾀﾘの時だけ処理したいのでこれでﾁｪｯｸ
	//{
	//	return;
	//}

	//auto itemID = [=]() 
	//{
	//	auto id = lpMapCtl.GetMapData(pos);
	//	return (id == MAP_ID::ITEM_RANDOM ? static_cast<MAP_ID>(ITEM_ID_START + GetRand(ITEM_MAX - 1)) : id);
	//};

	//auto parametorUP = [=](auto& parametorFlag, auto limnum)
	//{
	//	parametorFlag += (parametorFlag < limnum);
	//	lpMapCtl.SetMapData(pos, MAP_ID::NON);
	//};

	//switch (itemID())
	//{
	//	case MAP_ID::ITEM_FIRE_GUARD:
	//		parametorUP(fireGuardFlag, 1);
	//		break;
	//}
}
