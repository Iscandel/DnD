#include "Animation.h"

///////////////////////////////////////////////////////////////////////////////
// Constructeur
// Params : nombreImages	 -> Le nombre d'images dans l'animation
//			t				 -> Le type d'animation
//			tB				 -> Le type de boucle
//			tempsEntreImages -> La durée séparant 2 images en millisecondes
///////////////////////////////////////////////////////////////////////////////
Animation::Animation(unsigned int imageNumber,
					 AnimType t, 
					 LoopType tB, 
					 unsigned int timeBetweenImages)
:myAnimType(t)
,myLoopType(tB)
,myImageNumber(imageNumber)
,myFrameTime(timeBetweenImages)
,myIsFirstDirection(true)
,myCurrentImage(0)
,myIsStarted(false)
{
}

///////////////////////////////////////////////////////////////////////////////
// Destructeur
///////////////////////////////////////////////////////////////////////////////
Animation::~Animation(void)
{
}

///////////////////////////////////////////////////////////////////////////////
// Remet à zéro l'animation. Si resetImage vaut true, on réinitialise le
// sens le numéro d'image courante
///////////////////////////////////////////////////////////////////////////////
void Animation::reset(bool resetImage)
{
	if(resetImage)
	{
		myIsFirstDirection = true;
		myCurrentImage = 0;
	}
	myIsStarted = true;
}

///////////////////////////////////////////////////////////////////////////////
// Met à jour l'animation
///////////////////////////////////////////////////////////////////////////////
void Animation::update(unsigned int elapsedTime)
{
	myTime += elapsedTime;

	if(myIsStarted)
	{
		if(myTime > myFrameTime)
		{
			if(myIsFirstDirection)
			{
				if(myCurrentImage < getNbImages() - 1)
				{
					myCurrentImage++;
				}
				else
				{
					if(myLoopType == GO_BACK)
						myIsFirstDirection = false;
					else
						myCurrentImage = 0;

					if(myAnimType == UNIQUE)
					{
						myIsStarted = false;
						//monImageCourante = 0;
					}
					//numImage = 0;
				}
			}
			else
			{
				if(myCurrentImage > 0)
				{
					myCurrentImage--;
				}
				else
				{
					myIsFirstDirection = true;

					if(myAnimType == UNIQUE)
					{
						myIsStarted = false;
						//monImageCourante = 0;
					}
				}
			}
			myTime = 0;
		}
	}
}


