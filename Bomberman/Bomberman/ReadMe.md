
![Alt Text](Tile_Game/GameArt/GameLogo.PNG)


============================Team Members Information Begins======================================================================================

The game is written in c++ and is based on Directx 9.
Programmed By: 
	Nathan Contreras, Jacinto Molina, Kellen Walker 



============================Game Concept======================================================================================

Both Player will have a team of Fighting Squirrels that will be pinned against each other to the death in a turn based arena 
fighting. The game software is to outlast your opponent’s team of squirrels and make sure your team survives while the other 
team is destroyed. The first player to lose all of his Game team Loses.

============================GamePlay======================================================================================
--Game
This is a Turn based Game so every player will take turns after wasting their 4 movement points.
The Player will waster their momvements points by moving you'er unit.
To move the Unit the player will have to click on the unit and that he wants to move by clicking it with thier mouse.

--Automatic Game Logic
The Water tiles will start to flood the map after round 10 and all the units in the water tile will die.
This is done to pin the two teams closer to each other in combat.

============================Tile Types begin=======================================================================
	
Water Tile- Is the Death Tile that kills any units on tile while the level is flooding.
Grass Tile- Is the main tile in the game where the units will be able to walk on.
Stump Tile- Is the Collision where the units aren't able to cross or step on.

============================Unit in Game=======================================================================
There are Two types of Units in the Game Brown Medium Squirrel and Grey Medium Squirrel. 
All Squirrels will have the saame stats, which include

20 Health
	- Health until the player's unit Dies.
10 Attack-Powers 
	- Every attack on a unit will affect the opposing units 10 points.
4  Movement-Points  
	- There are 4 movement points in the round each unit will decrament from the movement points.

============================Class Info Begins======================================================================================

					Program Classes

Bomberman.cpp
   This class is the main source file for the game and Will have control over the game logic 
   in the game and will decide how the game is played. 
    
Unit class - 
	Will hold specific details on each unit and its specific unit type. Some details found in the 
	unit class include what type of unit it is, its attack power, its health, when it takes damage,
	or its position in the Game. Unit class will decide if the unit will also remove an action point from the player once moved.

Collision Manager Class –
	Manages all the collisions in the game between our game object.

TileDescParser Class – 
	Reads in a txt file that will have certain values that will affect the Game level and the game itself. 

Player class – 
	The Player class is in control of their unit’s movements and attacks in the game. The player class will 
	also only affect the unit selected by the player’s computer mouse. The player class also controls the collisions 
	by the units in the game and will determine if the units are able to move to a certain location.

TiledBackGround Class – 
	Generates a tile background that is formatted to be able to be drowned in the game.

GameUI Class – 
	will have control over what the player User Interface and will display the selected unit’s stats. 
	It will also display the movement points the player has remaining before the players turn is over.

========================================================================
    WIN32 APPLICATION : Bomberman Project Overview
========================================================================


AppWizard has created this Bomberman application for you.

This file contains a summary of what you will find in each of the class files that
make up your Bomberman application.


Bomberman.vcproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

/////////////////////////////////////////////////////////////////////////////
AppWizard has created the following resources:

Bomberman.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

Bomberman.ico
    This is an icon file, which is used as the application's icon (32x32).
    This icon is included by the main resource file Bomberman.rc.

small.ico
    This is an icon file, which contains a smaller version (16x16)
    of the application's icon. This icon is included by the main resource
    file Bomberman.rc.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Bomberman.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
