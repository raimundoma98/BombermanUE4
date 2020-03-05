Time spent: around 14/15 hours in 3 days.

Next steps:
 * Implement AI enemies that behave like players: 
  * The enemies would analize the game level, generating different points where they could move to. Then, they would choose the next movement to make based on some parameters.
  * Each point would have a value calculated using different parameters, such as the distance to other players, if a bomb blast can reach that location or the distance to pickups.
  * This way, different types of enemies could be modeled. For example: 
   * An agressive enemy would try to reach the location of other players and place bombs near to them.
   * A more strategic enemy would try to get pick ups to become stronger, picking up them and destroying destructible walls to get more pickups.
   * A pacific enemy would try to avoid bombs and would flee from other players.
 * Create different types of walls: 
  * Walls that could be moved by the players.
  * TNT walls that explode when a blast hits them, destroying nearby walls.
  * Destructible walls that stand for more than 1 blast.
 * Add animations to layers and bombs.
 * Create more pickups:
  * Bomb(False pickup) that is spawned by a destructible wall.