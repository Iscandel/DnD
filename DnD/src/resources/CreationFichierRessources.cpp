#include "CreationFichierRessources.h"
#include "ResourcesFile.h"
//#include "utiles/LectureFichier.h"
//#include "Coordonnees.h"

#include <vector>
#include <string>
#include <iostream>
//#include <SFML/System.hpp>
//#include <SFML/Graphics.hpp>
//
//#include "utiles/dirent.h"

namespace utiles
{
	void creerGuiDat()
{
	std::vector<std::string> fichiers;
	std::vector<std::string>IdFichiers;

	fichiers.push_back("./data/textures/tile1.png");
	fichiers.push_back("./data/textures/tile2.png");
	fichiers.push_back("./data/textures/tile3.png");
	fichiers.push_back("./data/textures/tile4.png");
	fichiers.push_back("./data/textures/tile5.png");
	fichiers.push_back("./data/textures/tile6.png");
	fichiers.push_back("./data/textures/tile7.png");
	fichiers.push_back("./data/textures/tile8.png");
	fichiers.push_back("./data/textures/tile9.png");
	fichiers.push_back("./data/textures/tile10.png");
	fichiers.push_back("./data/textures/tile11.png");
	fichiers.push_back("./data/textures/tile12.png");
	fichiers.push_back("./data/textures/tile13.png");
	fichiers.push_back("./data/textures/tile14.png");
	fichiers.push_back("./data/textures/tile15.png");
	fichiers.push_back("./data/textures/tile16.png");
	fichiers.push_back("./data/textures/wall.png");
	fichiers.push_back("./data/textures/player1.png");
	fichiers.push_back("./data/textures/dragoon.png");
	fichiers.push_back("./data/textures/player2.png");
	fichiers.push_back("./data/textures/treasure.png");

	ResourcesFile::getInstance()->create(fichiers, "./data/TexturesDat.dat");//, IdFichiers);

	std::cout << "DAT TexturesDat.dat créé" << std::endl;
}

	void createSounds()
	{
		std::vector<std::string> files;
		std::vector<std::string> id;

		files.push_back("./data/badMove.wav");
		id.push_back("badMove");

		files.push_back("./data/door.wav");
		id.push_back("door.wav");

		files.push_back("./data/dragoonMoves.wav");
		id.push_back("dragoonMoves");

		files.push_back("./data/dragoonAttacks.wav");
		id.push_back("dragoonAttacks");

		files.push_back("./data/dragoonWakesUp.wav");
		id.push_back("dragoonWakesUp");

		files.push_back("./data/p1NewTurn.wav");
		id.push_back("p1NewTurn");

		files.push_back("./data/p2NewTurn.wav");
		id.push_back("p2NewTurn");

		files.push_back("./data/move.wav");
		id.push_back("move");

		files.push_back("./data/treasureFound.wav");
		id.push_back("treasureFound");

		files.push_back("./data/wall.wav");
		id.push_back("wall");

		files.push_back("./data/win.wav");
		id.push_back("win");

		ResourcesFile::getInstance()->create(files, "./data/SoundDat.dat", id);
		
		std::cout << "DAT SoundDat.dat created" << std::endl;
	}
//void creerGuiDat()
//{
//	std::vector<std::string> fichiers;
//	std::vector<std::string>IdFichiers;
//
//	fichiers.push_back("./Donnees/ImagesMenu/seraph.png");
//	IdFichiers.push_back("AccueilImgFond");
//	
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/ValiderConnexion.png");
//	IdFichiers.push_back("AccueilBoutonValiderN");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/ValiderConnexionMove.png");
//	IdFichiers.push_back("AccueilBoutonValiderM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/ValiderConnexionClic.png");
//	IdFichiers.push_back("AccueilBoutonValiderC");
//
//	fichiers.push_back("./Donnees/ImagesMenu/liche2.png");
//	IdFichiers.push_back("PrincipalImgFond");
//
//	Curseurs
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/curseur.png");
//	IdFichiers.push_back("curseurNormal");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/64kCursorSpell-a.png");
//	IdFichiers.push_back("curseurSorts0");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/64kCursorSpell-b.png");
//	IdFichiers.push_back("curseurSorts1");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/64kCursorSpell-c.png");
//	IdFichiers.push_back("curseurSorts2");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/64kCursorSpell-d.png");
//	IdFichiers.push_back("curseurSorts3");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/64kCursorSpell-e.png");
//	IdFichiers.push_back("curseurSorts4");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/64kCursorSpell-f.png");
//	IdFichiers.push_back("curseurSorts5");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/64kCursorSpell-g.png.");
//	IdFichiers.push_back("curseurSorts6");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/64kCursorSpell-h.png.");
//	IdFichiers.push_back("curseurSorts7");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/64kCursorSpell-i.png");
//	IdFichiers.push_back("curseurSorts8");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/64kCursorSpell-j.png");
//	IdFichiers.push_back("curseurSorts9");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/64kCursorSpell-k.png");
//	IdFichiers.push_back("curseurSorts10");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/64kCursorSpell-l.png");
//	IdFichiers.push_back("curseurSorts11");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/EastCursor.png");
//	IdFichiers.push_back("curseurDroite");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/WestCursor.png");
//	IdFichiers.push_back("curseurGauche");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/NorthCursor.png");
//	IdFichiers.push_back("curseurHaut");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/NorthEastCursor.png");
//	IdFichiers.push_back("curseurDroiteHaut");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/NorthWestCursor.png");
//	IdFichiers.push_back("curseurHautGauche");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/SouthEastCursor.png");
//	IdFichiers.push_back("curseurBasDroite");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/SouthWestCursor.png");
//	IdFichiers.push_back("curseurGaucheBas");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/SouthCursor.png");
//	IdFichiers.push_back("curseurBas");
//	fichiers.push_back("./Donnees/ImagesMenu/curseurs/64kCursorAttack.PNG");
//	IdFichiers.push_back("curseurAttaque");
//
//	Gui en jeu
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/barreRaccourcis.PNG");
//	IdFichiers.push_back("barreRaccourcis");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonChatC.PNG");
//	IdFichiers.push_back("boutonChatC");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonChatM.PNG");
//	IdFichiers.push_back("boutonChatM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonEquipementC.PNG");
//	IdFichiers.push_back("boutonEquipementC");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonEquipementM.PNG");
//	IdFichiers.push_back("boutonEquipementM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonGroupeC.PNG");
//	IdFichiers.push_back("boutonGroupeC");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonGroupeM.PNG");
//	IdFichiers.push_back("boutonGroupeM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonJeterC.PNG");
//	IdFichiers.push_back("boutonJeterC");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonJeterM.PNG");
//	IdFichiers.push_back("boutonJeterM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonJeterN.PNG");
//	IdFichiers.push_back("boutonJeterN");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonMacrosC.PNG");
//	IdFichiers.push_back("boutonMacrosC");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonMacrosM.PNG");
//	IdFichiers.push_back("boutonMacrosM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonOptionsC.PNG");
//	IdFichiers.push_back("boutonOptionsC");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonOptionsM.PNG");
//	IdFichiers.push_back("boutonOptionsM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonReduireC.PNG");
//	IdFichiers.push_back("boutonReduireC");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonReduireN.PNG");
//	IdFichiers.push_back("boutonReduireN");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonReduireM.PNG");
//	IdFichiers.push_back("boutonReduireM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonSortsC.PNG");
//	IdFichiers.push_back("boutonSortsC");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonSortsM.PNG");
//	IdFichiers.push_back("boutonSortsM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonStatsC.PNG");
//	IdFichiers.push_back("boutonStatsC");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonReduireM.PNG");
//	IdFichiers.push_back("boutonReduireM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonReduireM.PNG");
//	IdFichiers.push_back("boutonReduireM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonStatsC.PNG");
//	IdFichiers.push_back("boutonStatsC");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonStatsM.PNG");
//	IdFichiers.push_back("boutonStatsM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/ecranChat.PNG");
//	IdFichiers.push_back("ecranChat");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/ecranEquipement.PNG");
//	IdFichiers.push_back("ecranEquipement");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/ecranOptions.PNG");
//	IdFichiers.push_back("ecranOptions");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/ecranStats.PNG");
//	IdFichiers.push_back("ecranStats");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/chatbox.PNG");
//	IdFichiers.push_back("chatbox");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kMainVitalityBar_(0,0)-(-68,0).bmp");
//	IdFichiers.push_back("glissierePv");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kMainEmptyBar_(0,0)-(-88,0).bmp");
//	IdFichiers.push_back("progressbarVieXpManaFond");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kMainExperienceBar_(0,0)-(-68,0).bmp");
//	IdFichiers.push_back("glissiereXp");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kMainManaBar_(0,0)-(-68,0).bmp");
//	IdFichiers.push_back("glissierePm");
//
//	Ecran stats
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/BoutonStat+N.PNG");
//	IdFichiers.push_back("boutonStat+N");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/BoutonStat+M.PNG");
//	IdFichiers.push_back("boutonStat+M");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/BoutonStat+C.PNG");
//	IdFichiers.push_back("boutonStat+C");
//
//	Ecran inventaire
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kEquipmentScrollButton.png");
//	IdFichiers.push_back("InventaireCurseurScrollbar");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/64kEquipmentPopUpBox_(0,0)-(-204,0).PNG");
//	IdFichiers.push_back("inventairePopUpConfirmationJeter");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonJeterN.PNG");
//	IdFichiers.push_back("inventaireBoutonJeterN");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonJeterM.PNG");
//	IdFichiers.push_back("inventaireBoutonJeterM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonJeterC.PNG");
//	IdFichiers.push_back("inventaireBoutonJeterC");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/64kEquipmentPopUpBoxButtonAcceptFrench_(0,0)-(-19,0).PNG");
//	IdFichiers.push_back("invDlgBoutonAccepterN");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/64kEquipmentPopUpBoxButtonCancelFrench_(0,0)-(-19,0).PNG");
//	IdFichiers.push_back("invDlgBoutonAnnulerN");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/64kEquipmentPopUpBoxButtonHighLightAcceptFrench_(0,0)-(-19,0).PNG");
//	IdFichiers.push_back("invDlgBoutonAccepterM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/64kEquipmentPopUpBoxButtonHighLightCancelFrench_(0,0)-(-19,0).PNG");
//	IdFichiers.push_back("invDlgBoutonAnnulerM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/64kEquipmentPopUpBoxButtonHighLightDownAcceptFrench_(0,0)-(-19,0).PNG");
//	IdFichiers.push_back("invDlgBoutonAccepterC");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/64kEquipmentPopUpBoxButtonHighLightDownCancelFrench_(0,0)-(-19,0).PNG");
//	IdFichiers.push_back("invDlgBoutonAnnulerC");
//	
//		
//		
//		
//		
//		
//	
//	Ecran Sorts
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/ecranSpellbook.PNG");
//	IdFichiers.push_back("ecranSpellbook");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookSignetAirRight_(0,0)-(-4,0).bmp");
//	IdFichiers.push_back("LivreDesSortsAir");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookSignetDarkRight_(0,0)-(-4,0).bmp");
//	IdFichiers.push_back("LivreDesSortsNecro");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookSignetEarthRight_(0,0)-(0,0).bmp");
//	IdFichiers.push_back("LivreDesSortsTerre");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookSignetLightRight_(0,0)-(-4,0).bmp");
//	IdFichiers.push_back("LivreDesSortsLumiere");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookSignetNoneRight_(0,0)-(-4,0).bmp");
//	IdFichiers.push_back("LivreDesSortsRien");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookSignetWaterRight_(0,0)-(-4,0).bmp");
//	IdFichiers.push_back("LivreDesSortsEau");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookSignetFireLeft_(0,0)-(-4,0).bmp");
//	IdFichiers.push_back("LivreDesSortsFeu");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookCornerR-a_(0,0)-(-68,0).bmp");
//	IdFichiers.push_back("LivreDesSortsPageG1");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookCornerR-b_(0,0)-(-68,0).bmp");
//	IdFichiers.push_back("LivreDesSortsPageG2");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookCornerR-c_(0,0)-(-68,0).bmp");
//	IdFichiers.push_back("LivreDesSortsPageG3");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookCornerR-d_(0,0)-(-68,0).bmp");
//	IdFichiers.push_back("LivreDesSortsPageG4");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookCornerR-e_(0,0)-(-68,0).bmp");
//	IdFichiers.push_back("LivreDesSortsPageG5");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookCornerR-f_(0,0)-(-68,0).bmp");
//	IdFichiers.push_back("LivreDesSortsPageG6");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookCornerR-g_(0,0)-(-68,0).bmp");
//	IdFichiers.push_back("LivreDesSortsPageG7");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookCornerR-h_(0,0)-(-68,0).bmp");
//	IdFichiers.push_back("LivreDesSortsPageG8");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookCornerL-a_(0,0)-(-80,0).bmp");
//	IdFichiers.push_back("LivreDesSortsPageD1");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookCornerL-b_(0,0)-(-80,0).bmp");
//	IdFichiers.push_back("LivreDesSortsPageD2");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookCornerL-c_(0,0)-(-80,0).bmp");
//	IdFichiers.push_back("LivreDesSortsPageD3");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookCornerL-d_(0,0)-(-80,0).bmp");
//	IdFichiers.push_back("LivreDesSortsPageD4");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookCornerL-e_(0,0)-(-80,0).bmp");
//	IdFichiers.push_back("LivreDesSortsPageD5");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookCornerL-f_(0,0)-(-80,0).bmp");
//	IdFichiers.push_back("LivreDesSortsPageD6");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookCornerL-g_(0,0)-(-80,0).bmp");
//	IdFichiers.push_back("LivreDesSortsPageD7");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kSpellBookCornerL-h_(0,0)-(-80,0).bmp");
//	IdFichiers.push_back("LivreDesSortsPageD8");
//
//	La croix
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonCroixN.PNG");
//	IdFichiers.push_back("boutonCroixN");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonCroixM.PNG");
//	IdFichiers.push_back("boutonCroixM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/boutonCroixC.PNG");
//	IdFichiers.push_back("boutonCroixC");
//
//	Les sorts actifs
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/64kStatusBackGround_(0,0)-(-20,0).png");
//	IdFichiers.push_back("SortsActifsFond");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/64kStatusBarUpPushed.png");
//	IdFichiers.push_back("SortsActifsFlecheHautC");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/64kStatusBarUp.png");
//	IdFichiers.push_back("SortsActifsFlecheHautN");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/64kStatusBarDownPushed.png");
//	IdFichiers.push_back("SortsActifsFlecheBasC");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/64kStatusBarDown.png");
//	IdFichiers.push_back("SortsActifsFlecheBasN");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/64kStatusEmptyBar_(0,0)-(24,0).png");
//	IdFichiers.push_back("SortsActifsGlissiere");
//
//	L'écran d'achats /vente
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/64kBuyBox_(0,0)-(-544,0).PNG");
//	IdFichiers.push_back("ecranAchatsVente");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kBuyArrowHighLightUp_(0,0)-(20,0).bmp");
//	IdFichiers.push_back("quantiteAchatVenteHautM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kBuyArrowHighLightDown_(0,0)-(20,0).bmp");
//	IdFichiers.push_back("quantiteAchatVenteBasM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kBuyArrowDownUp.bmp");
//	IdFichiers.push_back("quantiteAchatVenteHautC");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/64kBuyArrowDownDown.bmp");
//	IdFichiers.push_back("quantiteAchatVenteBasC");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/64kBuyButtonBuyFrench_(0,0)-(-32,0).PNG");
//	IdFichiers.push_back("boutonAchatN");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/64kBuyButtonHighLightBuyFrench_(0,0)-(-32,0).PNG");
//	IdFichiers.push_back("boutonAchatM");
//	fichiers.push_back("./Donnees/ImagesMenu/GUI_Jeu/newGui/GuiPNG/64kBuyButtonHighLightDownBuyFrench_(0,0)-(-32,0).PNG");
//	IdFichiers.push_back("boutonAchatC");
//
//	FichierRessources::getInstance()->creer(fichiers, "./Donnees/Gui/guiRessources.dat", IdFichiers);
//
//	std::cout << "DAT guiRessources.dat créé" << std::endl;
//}
//
//void creerTerrainDat()
//{
//	std::vector<std::string> fichiers;
//	std::ifstream input("./Donnees/ImagesJeu/Environnement/terrain.dat");
//	if (input == NULL)
//	{
//		std::cout << "Impossible de trouver le fichier d'images";
//		return;
//	}
//
//	std::string sType, nom;
//	int nbElements, nbTypes, id, offsetX, offsetY, typeSprite;
//	input >> nbElements;
//	input >> nbTypes;
//	for(int i = 0; i < nbTypes; i++)
//	{
//		input >> sType;
//	}
//	On passe le premier élément de type ....terrain, murs...
//	input >> sType;
//
//	int nbElementsLus = 0;
//	while(nbElementsLus < nbElements)
//	{
//		input >> nom;
//		
//		if(nom.find_first_of("#")==0)
//		{
//			input >> nom;
//		}
//
//		if(nom.find_first_of("#")!= 0)
//			fichiers.push_back(nom);
//
//		input >> offsetX >> offsetY;
//		input >> id;
//		input >> typeSprite;
//		
//		nbElementsLus++;
//	}
//
//	FichierRessources::getInstance()->creer(fichiers, "./Donnees/ImagesJeu/Environnement/terrainRessources.dat");
//
//	std::cout << "DAT terrainRessources.dat créé" << std::endl;
//
//	return true;
//}
//
//void creerBasiqueElementSkinsDat()
//{
//	std::vector<std::string> fichiers;
//
//	FichierTexte Fichier("./Donnees/ImagesJeu/Creatures/basiqueElementsSkin.dat");
//
//	if (!Fichier.estOuvert())
//	{
//		ILogger::log(ILogger::ERREURS) << "Impossible de trouver le fichier d'images basiqueElementsSkin.dat.\n";
//		return;
//		exit(EXIT_FAILURE);
//	}
//
//	std::string inutile, chemin ;
//	int nbEntites, id, numMode,direction, nbDirections;
//	unsigned int nbModes;
//
//	Fichier >> nbEntites;
//	
//	int nbElementsLus = 0;
//	while(nbElementsLus < nbEntites)
//	{
//		L'ID
//		Fichier >> id;
//
//		sf::Color couleur;
//		Fichier >> couleur;
//
//		Les modes
//		Fichier >> nbModes;
//
//		Les directions
//		Fichier >> nbDirections;
//
//		for(unsigned int i = 0; i < nbModes; i++)
//		{
//			Le numéro du mode
//			Fichier >> numMode;
//
//			La direction
//			int tmpDir = 0;
//			while(tmpDir < nbDirections) //<= 4)
//			{
//				Fichier >> direction;
//				chemin = Fichier.getArgument<std::string>();
//				int nbChemins =  Fichier.getArgument<int>();
//				int tmpChemin = 0;
//				while(tmpChemin < nbChemins)//.find_first_of("#")!=0)
//				{
//					chemin = Fichier.getArgument<std::string>();
//					fichiers.push_back(chemin);
//
//					Coordonnees offset;
//					Coordonnees offset2;
//					std::string sOffsets;
//
//					Fichier >> sOffsets;
//					std::istringstream flux(sOffsets);
//					flux >> offset.x >> offset.y >> offset2.x >> offset2.y;					
//
//					tmpChemin++;
//				}
//	
//				tmpSB.setId(id);
//				tmpDir++;
//			} //Fin while tmpDir
//		} //Fin nbModes
//
//		nbElementsLus++;
//	}//Fin nbEntites
//	
//	Tester la validité du fichier
//
//	Fichier.fermer();
//
//	FichierRessources::getInstance()->creer(fichiers, "./Donnees/ImagesJeu/Creatures/datBasiqueElementSkins.dat");
//	return;
//}
//
//void creerIconesDat()
//{
//	std::vector<std::string> fichiers;
//
//	std::ifstream input("./Donnees/ImagesJeu/Icones/Icones.dat");
//	if (input == NULL)
//	{
//		std::cout << "Impossible de trouver le fichier d'images Icones.dat";
//		return;
//	}
//
//	std::string inutile, chemin ;
//	int nbIcones, id, r,g,b,nbImages,offX, offY, off2X, off2Y, nbSons;
//	input >> nbIcones;
//	
//	for(int i = 0; i < nbIcones; i++)
//	{
//		input >> inutile;
//	}
//	int nbElementsLus = 0;
//	while(nbElementsLus < nbIcones)
//	{
//		On passe le premier nom du skin
//		input >> inutile;
//
//		On récupère l'ID
//		input >> inutile;
//		input >> id;
//
//		On récupère la couleur de transparence
//		input >> inutile;
//		input >> r >> g >> b;
//
//		Les sons
//		input >> inutile;
//		input >> nbSons;
//		if(nbSons != 0)
//		{
//			Le type de son (aléatoire ou non)
//			input >> inutile;
//			input >> inutile;
//			L'ID du son Cas de plusieurs sons... ????????????????????????????
//			input >> inutile;
//			input >> inutile;
//		}
//
//		On récupère le nombre d'images, au cas où l'icone serait animée
//		input >> inutile;
//		input >> nbImages;
//
//		for(int j = 0; j < nbImages; j++)
//		{
//			On récupère le chemin
//			input >> chemin;
//			fichiers.push_back(chemin);
//
//			On récupère les offsets
//			input >> offX >> offY >> off2X >> off2Y;
//
//		}
//		nbElementsLus++;
//	}
//	input.close();
//
//	FichierRessources::getInstance()->creer(fichiers, "./Donnees/ImagesJeu/Icones/datIcones.dat");
//	std::cout << "DAT datIcones.dat créé" << std::endl;
//}
//
//void utiles::creerSortsDat()
//{
//	std::vector<std::string> fichiers;
//
//	std::ifstream input("./Donnees/ImagesJeu/Sorts/basiquesEffetsSorts.dat");
//	if (input == NULL)
//	{
//		std::cout << "Impossible de trouver le fichier d'images basiquesEffetsSorts.dat\n";
//	}
//
//	std::string inutile, chemin ;
//	int nbEffetsBasiques, id, r, g, b, offsetX, offsetY,
//									offset2X, offset2Y, typeAnim, direction, maxTmpDir;
//	input >> nbEffetsBasiques;
//	
//	for(int i = 0; i < nbEffetsBasiques; i++)
//	{
//		input >> inutile;
//	}
//	int nbElementsLus = 0;
//	while(nbElementsLus < nbEffetsBasiques)
//	{
//		On passe le premier nom du skin
//		input >> inutile;
//
//		On récupère l'ID
//		input >> inutile;
//		input >> id;
//
//		On récupère la couleur de transparence
//		input >> inutile;
//		input >> r >> g >> b;
//
//		On récupère le type d'animation : statique ou mobile
//		input >> inutile;
//		input >> typeAnim;
//
//		int maxTmpDir = typeAnim == BasiqueEffetVisuel::MOBILE ? 4 : 0;
//		On récupère le nombre de directions
//		input >> inutile;
//		input >> maxTmpDir;
//
//		La direction
//		input >> inutile;
//		int tmpDir = 0;
//
//		while(tmpDir < maxTmpDir)
//		{
//			input >> direction;
//			input >> chemin;
//			while(chemin.find_first_of("#")!=0)
//			{
//				input >> offsetX >> offsetY >> offset2X >> offset2Y;
//
//				fichiers.push_back(chemin);
//
//				input >> chemin;
//			}
//			tmpDir++;
//		} //Fin while tmpDir
//		nbElementsLus++;
//	}
//
//	FichierRessources::getInstance()->creer(fichiers, "./Donnees/ImagesJeu/Sorts/datSorts.dat");
//	std::cout << "DatSorts créé" << std::endl;
//}
//
///////////////////////////////////////////////////////////////////////////
// Pour les sons et bruitages
///////////////////////////////////////////////////////////////////////////
//void creerSonsDat()
//{
//	DIR* Repertoire = opendir("../Extracted/");
//
//	struct dirent *listeFichiers;
//	std::ofstream output("./Donnees/listeSorts.txt");
//	
//	while ((listeFichiers = readdir(Repertoire)) != 0)
//	{
//		std::string nom(listeFichiers->d_name );
//
//		if(nom != "." && nom != "..")
//		{
//			output << nom << "\n";
//		}
//	}
//	closedir(Repertoire);
//
//
//	std::vector<std::string> fichiers;
//	std::vector<std::string> IdFichiers;
//
//	std::string base = "../Extracted/";
//
//	FichierTexte Fichier("./Donnees/listeSorts2.txt");
//
//	if (!Fichier.estOuvert())
//	{
//		ILogger::log(ILogger::ERREURS) << "Impossible de trouver le fichier d'images listeSorts2.txt.\n";
//		return;
//	}
//
//	std::string chemin;
//	std::string id;
//
//	while(!Fichier.eof() && !Fichier.erreurFlux())
//	{
//		Fichier >> chemin;
//		Fichier >> id;
//
//		fichiers.push_back(base + chemin);
//		IdFichiers.push_back(id);
//		std::cout << chemin << std::endl;
//	}
//
//	if(Fichier.erreurFlux())
//		ILogger::log(ILogger::ERREURS) << "Erreur en créant le dat sons.dat\n"; 
//	
//	FichierRessources::getInstance()->creer(fichiers, "./Donnees/Audio/sons.dat", IdFichiers);
//	std::cout << "DatSons créé" << std::endl;
//
//}

};