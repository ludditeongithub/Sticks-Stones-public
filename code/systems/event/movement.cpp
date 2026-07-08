void prepareNextMovementWandering()
{
		
}

void setNextMovementInertia() {}

else if (actions[i] == Action::Prowl ||
			 actions[i] == Action::CheckProwl)
		{ // TODO: ProwlTile
			if (rint(0, 50) < 50)
				directions[i] = getRandomAdjDirection(directions[i]);
			moveInDirection(i, false);
			// check surroundings, if target is now seen
			Object obj = currentTarget[i];
			if (actions[i] = Action::CheckProwl)
				ran = true;
			if (isItem(obj))
				itemCheck(pawn, directions[i], ran);
			else if (isPlant(obj))
				searchPlantCheck(pawn, directions[i], ran);
			else if (isScavengeable(obj))
				scavengeableCheck(pawn, directions[i], ran);
			// TODO:: Fruit
			// TODO:: animal
			else if (isTools(obj))
				toolCheck(pawn);
			inertias[i] = calcSpeed(midSpeedPawn, coords[i]);
		}
		else if (actions[i] == Action::ApproachPlant ||
			 actions[i] == Action::ApproachTile ||
			 actions[i] == Action::ApproachTool ||
			 actions[i] == Action::ApproachItem)
		{
			std::pair<Direction, bool> next = nextDirectionToTarget(i);
			direction[i] = next.first;
			if (next.second)
			{
				moveInDirection(i, false);
				inertias[i] = calcSpeed(minSpeedPawn, coords[i]);
			}
			else
			{
				if (actions[i] == Action::ApproachItem)
					takeItem(i, coords[i]);
				else if (actions[i] == Action::ApproachPlant)
					harvestPlant(i, coords[i]);
				else if (actions[i] == Action::ApproachTile)
					harvestTile(i, coords[i]);
				else if (actions[i] == Action::ApproachScavengeable)
					harvestScavengeable(i, coords[i]);
				else if (actions[i] == Action::ApproachTool)
					takeTool(i, coords[i]);
				actions[i] = Action::Idle;
				decideTask(i);
			}
		}
		else if (actions[i] == Action::GetTool ||
			 actions[i] == Action::GetItem)
		{
			std::pair<Direction, bool> next = nextDirectionToTarget(i);
			direction[i] = next.first;
			if (next.second)
			{
				moveInDirection(i, false);
				inertias[i] = calcSpeed(midSpeedPawn, coords[i]);
				// promised versions, while approach is non-promise
				if (actions[i] == Action::GetItem)
					takeItem(i, coords[i]);
				else
					takeTool(i, coords[i]);
				actions[i] = Action::Idle;
				findPromise.set();
			}
			else if (actions[i] == Action::Pursuit ||
				 actions[i] == Action::AnimalPursuit)
			{
				std::pair<Direction, bool> next = nextDirectionToMovingTarget(i);
				direction[i] = next.first;
				if (next.second)
					moveInDirection(i, false);
				else
				{
					if (actions[i] == Action::Pursuit)
					{
						// TODO: get new military target
						if (attack(i, currentDest[i], false, false))
							getNewTarget();
					}
					// TODO: do this
					if (actions[i] == Action::AnimalPursuit)
						if (attack(i, currentDest[i], false, true))
							dealWithGame();
				}
				inertias[i] = calcSpeed(maxSpeedPawn, coords[i]);
			}
		}
