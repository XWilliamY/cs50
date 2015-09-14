//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// height and width of game's paddle in pixels
#define PHEIGHT 10
#define PWIDTH 60

// height and width of bricks
#define BrHEIGHT 10
#define BrWIDTH 35

// y value of game's paddle
#define PY 550

// x and y of game's ball
#define BX 190
#define BY 280

// radius of ball
#define BRADIUS 10

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);
    setFont(label, "SansSerif-60");
    setColor(label, "LIGHT_GRAY");
    updateScoreboard(window, label, 0);
    add(window, label);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // initializing additional variables
    double x;
    double xvelocity = drand48() + 2;
    double yvelocity = drand48() + 2;
    
    waitForClick();
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {   
        // check for mouse movement
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // move paddle horizontally 
                x = getX(event);
                if(x <= 340)
                {
                    setLocation(paddle, x, PY); 
                }
                else if(x > 340)
                {   
                    x = getX(event) - getWidth(paddle); 
                }              
            }
        }
        
        //keep ball moving
        
        move(ball, xvelocity, yvelocity);

        // bounce off right or left edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window) || getX(ball) <= 0)
        {
            xvelocity = -xvelocity;
        }

        // bounce off top of window 
        else if (getY(ball) <= 0)
        {
            yvelocity = -yvelocity;
        }
        
        // detect collision
        GObject object = detectCollision(window, ball);
        
        if(object != NULL)
        {
            // bounces off paddle
            if(object == paddle)
            {
                yvelocity = -yvelocity;
            }
        
            else if(strcmp(getType(object), "GRect") == 0)
            {
                yvelocity = -yvelocity;
                removeGWindow(window, object);
                points++;
                bricks--;
                updateScoreboard(window, label, points);
            }
        }
        
        // if ball reaches bottom wall
        if(getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives --;
            setLocation(ball, 190, 280);
            waitForClick();
        }
        
        // linger before moving again
        pause(10);
    }

    // wait for click before exiting
    waitForClick();
    
    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{

    GRect rects[COLS][ROWS];
    for(int i = 0; i < ROWS; i++)
    {   
        for(int j = 0; j < COLS; j++)
        {   
            // starts at x = 2 to balance both sides
            // we add an addition 5 to add some space between each block 
            rects[i][j] = newGRect(2 + (j * (BrWIDTH + 5)) , 40 + (i * (BrHEIGHT + 5)), BrWIDTH, BrHEIGHT);
          
            if(i == 0)
            {
                setColor(rects[i][j], "RED");
            } 
            else if(i == 1)
            {
                setColor(rects[i][j], "ORANGE"); 
            }
            else if(i == 2)
            {
                setColor(rects[i][j], "YELLOW");
            }
            else if(i == 3)
            {
                setColor(rects[i][j], "GREEN");
            }
            else
            {
                setColor(rects[i][j], "CYAN");
            }
            setFilled(rects[i][j], true);
            add(window, rects[i][j]);
        }
    }   
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    return newGOval(190, 280, BRADIUS*2, BRADIUS*2);
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    return newGRect(170, 550, PWIDTH, PHEIGHT);
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    return newGLabel("0");
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);
    
    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
