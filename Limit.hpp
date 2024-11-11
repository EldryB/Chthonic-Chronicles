#pragma once
#include "MovementComponent.hpp"

void MovementComponent::setLvl1Limits(sf::Sprite* spr, float& lastx, float& lasty)
{
	if (stages == CurrentStage::Lvl1R1)
	{
		if (getXPos(spr) < 50 && (getYPos(spr) < 321 || getYPos(spr) > 414))
		{
			spr->setPosition(lastx, lasty);
		}


		if (getYPos(spr) < 183 || getYPos(spr) > 509)
		{
			spr->setPosition(lastx, lasty);
		}
	}

	else if (stages == CurrentStage::Lvl1R2)
	{
		if (getXPos(spr) > 718 && getXPos(spr) < 955 && (getYPos(spr) < 321 || getYPos(spr) > 414))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 660 && getXPos(spr) <= 718 && (getYPos(spr) < 277 || getYPos(spr) > 414))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 600 && getXPos(spr) <= 660 && (getYPos(spr) < 229 || getYPos(spr) > 461))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 430 && getXPos(spr) <= 600 && (getYPos(spr) < 179 || getYPos(spr) > 508))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 335 && getXPos(spr) <= 430 && (getYPos(spr) > 508))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 160 && getXPos(spr) <= 335 && (getYPos(spr) < 179 || getYPos(spr) > 508))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 99 && getXPos(spr) <= 160 && (getYPos(spr) < 229 || getYPos(spr) > 461))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 43 && getXPos(spr) <= 99 && (getYPos(spr) < 277 || getYPos(spr) > 414))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) <= 43)
		{
			spr->setPosition(lastx, lasty);
		}
	}

	else if (stages == CurrentStage::Lvl1R3)
	{
		if (getXPos(spr) <= 41)
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 41 && getXPos(spr) <= 186 && (getYPos(spr) < 154 || getYPos(spr) > 425))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 186 && getXPos(spr) <= 335 && (getYPos(spr) > 425))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 335 && getXPos(spr) <= 430 && (getYPos(spr) < 154))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 430 && getXPos(spr) <= 770 && (getYPos(spr) < 154 || getYPos(spr) > 425))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 770 && (getYPos(spr) < 248 || getYPos(spr) > 331))
		{
			spr->setPosition(lastx, lasty);
		}
	}

	else if (stages == CurrentStage::Lvl1R4)
	{
		if (getXPos(spr) > 48 && getXPos(spr) <= 91 && (getYPos(spr) < 248 || getYPos(spr) > 331))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 91 && getXPos(spr) <= 178 && (getYPos(spr) < 248 || getYPos(spr) > 422))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 178 && getXPos(spr) <= 602 && (getYPos(spr) < 341 || getYPos(spr) > 422))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 602 && getXPos(spr) <= 684 && (getYPos(spr) < 295 || getYPos(spr) > 422))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 684 && getXPos(spr) <= 900 && (getYPos(spr) < 295 || getYPos(spr) > 375))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 900)
		{
			spr->setPosition(lastx, lasty);
		}
	}

	else if (stages == CurrentStage::Lvl1R5)
	{
		if (getXPos(spr) > 714 && getXPos(spr) <= 955 && (getYPos(spr) < 314 || getYPos(spr) > 393))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 657 && getXPos(spr) <= 714 && (getYPos(spr) < 273 || getYPos(spr) > 393))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 597 && getXPos(spr) <= 657 && (getYPos(spr) < 223 || getYPos(spr) > 440))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 335 && getXPos(spr) <= 597 && (getYPos(spr) < 174 || getYPos(spr) > 485))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 186 && getXPos(spr) <= 335 && (getYPos(spr) < 174))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 128 && getXPos(spr) <= 186 && (getYPos(spr) < 222 || getYPos(spr) > 435))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 72 && getXPos(spr) <= 128 && (getYPos(spr) < 265 || getYPos(spr) > 386))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 45 && getXPos(spr) <= 72 && (getYPos(spr) < 309 || getYPos(spr) > 386))
		{
			spr->setPosition(lastx, lasty);
		}
	}

	else if (stages == CurrentStage::Lvl1R6)
	{
		if (getXPos(spr) > 45 && getXPos(spr) <= 129 && (getYPos(spr) < 314 || getYPos(spr) > 393))
		{
			spr->setPosition(lastx, lasty);
		}
		else if (getXPos(spr) > 129 && getXPos(spr) <= 742 && (getYPos(spr) < 260 || getYPos(spr) > 455))
		{
			spr->setPosition(lastx, lasty);
		}
		else if(getXPos(spr) > 742)
		{
			spr->setPosition(lastx, lasty);
		}
	}

	else if (stages == CurrentStage::Lvl1R7)
	{
		if (getXPos(spr) > 882 && getXPos(spr) <= 955 && (getYPos(spr) < 309 || getYPos(spr) > 386))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 825 && getXPos(spr) <= 882 && (getYPos(spr) < 262 || getYPos(spr) > 386))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 765 && getXPos(spr) <= 825 && (getYPos(spr) < 216 || getYPos(spr) > 465))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 702 && getXPos(spr) <= 765 && (getYPos(spr) < 170 || getYPos(spr) > 480))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 578 && getXPos(spr) <= 702 && (getYPos(spr) < 310 || getYPos(spr) > 390))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 360 && getXPos(spr) <= 578 && (getYPos(spr) < 172 || getYPos(spr) > 480))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 271 && getXPos(spr) <= 360 && (getYPos(spr) < 172))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 61 && getXPos(spr) <= 271 && (getYPos(spr) < 172 || getYPos(spr) > 480))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) <= 61)
		{
			spr->setPosition(lastx, lasty);
		}
	}

	else if (stages == CurrentStage::Lvl1R8)
	{
		if (getXPos(spr) > 675)
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 622 && getXPos(spr) <= 675 && (getYPos(spr) < 213 || getYPos(spr) > 460))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 566 && getXPos(spr) <= 622 && (getYPos(spr) < 169 || getYPos(spr) > 460))
		{
			spr->setPosition(lastx, lasty);
		}
	}

}

void MovementComponent::setMainStageLimits(sf::Sprite* spr, float& lastx, float& lasty)
{
	if (false)
	{
		if(false)
		{
			spr->setPosition(lastx, lasty);
		}
	}

	else
	{
		if (getXPos(spr) > 868 && getXPos(spr) <= 990 && ((getYPos(spr) > 268 && getYPos(spr) < 318) || (getYPos(spr) < 194) || getYPos(spr) > 443))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 817 && getXPos(spr) <= 868 && ((getYPos(spr) > 268 && getYPos(spr) < 318) || (getYPos(spr) < 194) || getYPos(spr) > 424))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 768 && getXPos(spr) <= 817 && ((getYPos(spr) > 268 && getYPos(spr) < 318) || (getYPos(spr) < 194) || getYPos(spr) > 407))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 722 && getXPos(spr) <= 768 && ((getYPos(spr) < 194) || getYPos(spr) > 390))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 629 && getXPos(spr) <= 722 && ((getYPos(spr) > 268 && getYPos(spr) < 318) || (getYPos(spr) < 194) || getYPos(spr) > 370))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 603 && getXPos(spr) <= 629 && ((getYPos(spr) > 192 && getYPos(spr) < 318)) )
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 546 && getXPos(spr) <= 603 && ((getYPos(spr) < 252 || getYPos(spr) > 369)))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 516 && getXPos(spr) <= 546 && ((getYPos(spr) > 192 && getYPos(spr) < 306)))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 380 && getXPos(spr) <= 516 && ((getYPos(spr) > 252 && getYPos(spr) < 306) || (getYPos(spr) < 194) || getYPos(spr) > 372))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 280 && getXPos(spr) <= 380 && ((getYPos(spr) > 252 && getYPos(spr) < 306) || (getYPos(spr) < 194) || getYPos(spr) > 408))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) > 230 && getXPos(spr) <= 280 && ((getYPos(spr) < 194) || getYPos(spr) > 426))
		{
			spr->setPosition(lastx, lasty);
		}


		else if (getXPos(spr) > 41 && getXPos(spr) <= 230 && ((getYPos(spr) > 252 && getYPos(spr) < 306) || (getYPos(spr) < 194) || getYPos(spr) > 445))
		{
			spr->setPosition(lastx, lasty);
		}

		else if (getXPos(spr) <= 41 && ((getYPos(spr) < 305) || getYPos(spr) > 386))
		{
			spr->setPosition(lastx, lasty);
		}
	}
}