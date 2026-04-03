
{ paste source code from a C header (.h) file into this file }

{ fictional test source code }
{

/**
 * Fictional comment of a fictional type
 */
typedef Uint64 SDL_FictionalType;

#define SDL_FI1  0x0000000000000001    /**< FI 1 Comment */
#define SDL_FI2  0x0000000000000002    /**< FI 2 Comment */
#define SDL_FI3  0x0000000000000004    /**< FI 3 Comment */

/**
 * Fictional comment of a fictional function
 */
extern SDL_DECLSPEC bool SDLCALL FictionalFunction(SDL_FictionalID fictionalID, SDL_Rect *rect);

}
