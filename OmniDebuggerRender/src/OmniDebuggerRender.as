package
{
	import ODGame.ODGameLib.CModule;
	import ODGame.ODGameLib.ram;
	
	import flash.display.*;
	import flash.events.*;
	import flash.media.Sound;
	import flash.media.SoundChannel;
	import flash.media.SoundMixer;
	import flash.media.SoundTransform;
	import flash.net.URLRequest;
	import flash.text.*;
	import flash.utils.getTimer;
	
	import mx.utils.StringUtil;
	
	[SWF(width='512',height='512',frameRate='60')]
	public class OmniDebuggerRender extends Sprite
	{
		private var m_odgame:ODGame;
		private var m_odgameData:ODGameData;
		private var outputformat:TextFormat
		private var deltaTime:Number;
		private var time:Number;
		private var score:int;
		
		private var isPlayerDead:Boolean;
		private var timeLasted:Number;
		
		[Embed(source="assets/npc00.png")]
		private var npc00BitmapClass:Class;
		[Embed(source="assets/npc01.png")]
		private var npc01BitmapClass:Class;
		[Embed(source="assets/npc02.png")]
		private var npc02BitmapClass:Class;
		[Embed(source="assets/npc03.png")]
		private var npc03BitmapClass:Class;
		[Embed(source="assets/teemo.png")]
		private var playerBitmapClass:Class;
		private var playerSprite:Sprite;
		[Embed(source="assets/bullet.png")]
		private var bulletBitmapClass:Class;
		private var bulletbitmap:Bitmap;
		private var npcSprites:Array;
		[Embed(source="assets/ali.png")]
		private var aliBitmapClass:Class;
		[Embed(source="assets/background.png")]
		private var backgroundClass:Class;
		
		[Embed(source="assets/BGM.mp3")]
		private var bgmSoundClass:Class;
		private var bgmSound:Sound;
		private var bgmSoundChannel:SoundChannel;
		[Embed(source="assets/bullet.mp3")]
		private var bulletSoundClass:Class;
		private var bulletSound:Sound;
		[Embed(source="assets/dying.mp3")]
		private var dyingSoundClass:Class;
		private var dyingSound:Sound;
		[Embed(source="assets/laugh.mp3")]
		private var laughSoundClass:Class;
		private var laughSound:Sound;
		
		private static const COMMAND_LEFT:int = 0;
		private static const COMMAND_RIGHT:int = 1;
		private static const COMMAND_UP:int = 2;
		private static const COMMAND_DOWN:int = 3;
		private static const WEST:int = 0;
		private static const NORTH:int = 1;
		private static const EAST:int = 2;
		private static const SOUTH:int = 3;
		
		public function OmniDebuggerRender()
		{
			CModule.startAsync(this);
			
			initResource();
						
			m_odgame = ODGame.create();
			m_odgame.Reset();
			
			m_odgameData = new ODGameData();
			m_odgameData.swigCPtr = m_odgame.getODGameData();
			
			isPlayerDead = false;
			timeLasted = 0;
			
			var background:Bitmap = new backgroundClass();
			stage.addChild(background);
			stage.addChild(this);
						
			outputformat = new TextFormat();
			outputformat.size = 18;
			outputformat.align = TextFormatAlign.CENTER;
			var tipsOutput:TextField = new TextField();
			tipsOutput.width = 512;
			tipsOutput.height = 512;
			tipsOutput.y = 80;
			tipsOutput.text = "Tips:\n";
			tipsOutput.appendText("Little teemo, They're trying to hurt you\n");
			tipsOutput.appendText("Stay away with the bullets \n");
			tipsOutput.appendText("You'll got a score each time the bullets kill themself \n\n");
			tipsOutput.appendText("Movement:\n");
			tipsOutput.appendText("Press \'A\' to move left \n");
			tipsOutput.appendText("Press \'S\' to move down \n");
			tipsOutput.appendText("Press \'D\' to move right \n");
			tipsOutput.appendText("Press \'W\' to move up \n\n");
			tipsOutput.appendText("Click to start");
			tipsOutput.setTextFormat(outputformat);
			stage.addEventListener(MouseEvent.CLICK, startHandler);
			addChild(tipsOutput);
		}
		
		private function startHandler(event:MouseEvent):void
		{
			stage.addEventListener(Event.ENTER_FRAME, enterFrameHandler);
			stage.addEventListener(KeyboardEvent.KEY_DOWN, keydownHandler);
			stage.addEventListener(KeyboardEvent.KEY_UP, keyupHandler);
			stage.removeEventListener(MouseEvent.CLICK, startHandler);
			
			time = getTimer();
			bgmSoundChannel = bgmSound.play(0, 0);
		}
				
		private function initResource():void
		{
			bgmSound = new bgmSoundClass() as Sound;
			bgmSoundChannel = new SoundChannel();
			
			bulletSound = new bulletSoundClass() as Sound;
			
			dyingSound = new dyingSoundClass() as Sound;
			laughSound = new laughSoundClass() as Sound;
		
			var playerbitmap:Bitmap = new playerBitmapClass();
			playerSprite = new Sprite();
			playerSprite.addChild(playerbitmap);
			
			bulletbitmap = new bulletBitmapClass();
			
			var bitmap:Bitmap = Bitmap(new npc00BitmapClass());
			var bitmapArray:Array = new Array();
			bitmapArray.push(bitmap);
			
			bitmap = new npc01BitmapClass();
			bitmapArray.push(bitmap);
			
			bitmap = new npc02BitmapClass();
			bitmapArray.push(bitmap);
			
			bitmap = new npc03BitmapClass();
			bitmapArray.push(bitmap);
			
			npcSprites = new Array();
			for (var i:int = 0; i < bitmapArray.length; ++i)
			{
				var tmpsprite:Sprite = new Sprite();
				tmpsprite.addChild(bitmapArray[i]);
				npcSprites.push(tmpsprite);
			}
		}
		
		private function keydownHandler(event:KeyboardEvent):void
		{
			var charFromKey:String = String.fromCharCode(event.charCode).toLowerCase();
			
			switch (charFromKey)
			{
				case "a":
				{
					m_odgame.UpdateCommand(COMMAND_LEFT, true);
					break;
				}
				case "d":
				{
					m_odgame.UpdateCommand(COMMAND_RIGHT, true);
					break;
				}
				case "s":
				{
					m_odgame.UpdateCommand(COMMAND_DOWN, true);
					break;
				}
				case "w":
				{
					m_odgame.UpdateCommand(COMMAND_UP, true);
					break;
				}
			}
		}
		
		private function keyupHandler(event:KeyboardEvent):void
		{
			var charFromKey:String = String.fromCharCode(event.charCode).toLowerCase();
			
			switch (charFromKey)
			{
				case "a":
				{
					m_odgame.UpdateCommand(COMMAND_LEFT, false);
					break;
				}
				case "d":
				{
					m_odgame.UpdateCommand(COMMAND_RIGHT, false);
					break;
				}
				case "s":
				{
					m_odgame.UpdateCommand(COMMAND_DOWN, false);
					break;
				}
				case "w":
				{
					m_odgame.UpdateCommand(COMMAND_UP, false);
					break;
				}
			}
		}
		
		private function enterFrameHandler(event:Event):void
		{
			if (isPlayerDead)
			{
				handlePlayerDeath();
				return ;
			}
			update();
			render();
		}
		
		private function handlePlayerDeath():void 
		{
			stage.removeEventListener(Event.ENTER_FRAME, enterFrameHandler);
			var scoreOutput:TextField = new TextField();
			scoreOutput.width = 512;
			scoreOutput.text = "You die bravely !!!\n";
			scoreOutput.appendText("You've lasted for : " + timeLasted /1000 + " Seconds\n");
			scoreOutput.appendText("And you've slain : " + score + " Badguys");
			scoreOutput.setTextFormat(outputformat);
			scoreOutput.y = height /6;
			removeChildren();
			addChild(scoreOutput);
			
			var aliBitmat:Bitmap = new aliBitmapClass();
			var aliSprite:Sprite = new Sprite();
			aliSprite.addChild(aliBitmat);
			aliSprite.addEventListener(MouseEvent.CLICK, handleRestart);
			aliSprite.x = (width - aliSprite.width)/2;
			aliSprite.y = scoreOutput.height + scoreOutput.y;
			addChild(aliSprite);
			
			var restartText:TextField = new TextField();
			restartText.text = "\"Click me to Try again\"";
			restartText.setTextFormat(outputformat);
			
			restartText.y = aliSprite.y + aliSprite.height;
			restartText.width = 512;
			addChild(restartText);
			isPlayerDead = false;
			score = 0;
			bgmSoundChannel.stop();
			SoundMixer.stopAll();
			dyingSound.play(0, 0);
		}
		
		private function handleRestart(event:Event):void
		{
			m_odgame.Reset();
			stage.addEventListener(Event.ENTER_FRAME, enterFrameHandler);
			timeLasted = 0;
			time = getTimer();
			isPlayerDead = false;

			bgmSoundChannel = bgmSound.play(0, 0);
		}
		
		private function update():void
		{
			var delta:Number;
			delta = getTimer() - time;
			timeLasted += delta;
			time = getTimer();
			m_odgame.Update(delta/1000);
		}
		
		private function render():void
		{
			if (score < m_odgameData.score)
			{
				score = m_odgameData.score;
				laughSound.play(0, 0);
			}
			removeChildren();
			
			var playerData:PlayerData = new PlayerData();
			playerData.swigCPtr = m_odgameData.playerData;
			
			if (!playerData.isAlive)
			{
				isPlayerDead = true;
			}
			playerSprite.x = playerData.posX;
			playerSprite.y = playerData.posY;
					
			var npcData:NpcData = new NpcData();
			for (var i:int = 0; i < 4; ++i)
			{
				npcData.swigCPtr = m_odgameData.npcData;
				npcData.swigCPtr += i * npcData.npcDataSize;
				if(npcData.isAlive)
				{
					npcSprites[i].x = npcData.posX;
					npcSprites[i].y = npcData.posY;	
					if (npcData.bFired)
					{
						bulletSound.play(0, 0);
					}
					
					addChild(npcSprites[i]);
				}
			}
			
			var bulletData:BulletData = new BulletData();
			bulletData.swigCPtr = m_odgameData.bulletsData;
			var size:int = bulletData.bulletDataSize;
			
			var bulletSprites:Array = new Array();
			for (i = 0; i < m_odgameData.bulletsNumber; ++i)
			{
				var bulletSprite:Sprite = new Sprite();
				var varbullbitmap:Bitmap = new bulletBitmapClass();
				bulletSprite.addChild(varbullbitmap);
				bulletData.swigCPtr = m_odgameData.bulletsData + i * size ;
				bulletSprite.x = bulletData.posX;
				bulletSprite.y = bulletData.posY;

				
				bulletSprites.push(bulletSprite);
			}

			for (i = 0; i < bulletSprites.length; ++i)
			{
				addChild(bulletSprites[i]);
			}
			
			addChild(playerSprite);
			
		}
	}
}