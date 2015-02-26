//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10
#define CIRCUMFERENCE (RADIUS * 2)
#define VELOCITY 4.0
// lives
#define LIVES 3

// paddle
#define PADDLE_WIDTH 70
#define PADDLE_HEIGHT 10

// brick constants
#define BRICK_WIDTH 35
#define BRICK_HEIGHT 10
#define BRICK_SPACE 5
#define BRICK_DISTANCE_TOP 50
const string brick_colors[] = {"RED","ORANGE","YELLOW","GREEN","BLUE"};

// prototypes
void initBricks(GWindow window);
void initBallMovement(GWindow window);
void moveBall(GWindow window, GOval ball, double velocity);
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
    int ball_centered_x = (getWidth(window) / 2) - RADIUS,
    int ball_centered_y = (getHeight(window) / 2) - RADIUS,
    int x_velocity = 0;
    int y_velocity = 0;

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel scoreboard  = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    bool game_started = false;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // move ball
        move(ball, x_velocity, y_velocity);

        // ball collided with bottom wall
        // - lose a life
        // - reset the game ball and position
        if (getY(ball) + CIRCUMFERENCE >= getHeight(window))
        {   
            lives--;
            game_started = false;
            setLocation(ball, ball_centered_x, ball_centered_y);
            x_velocity = 0;
            y_velocity = 0;
            move(ball, x_velocity, y_velocity);
        }
        else if (getY(ball) <= 0)
        {
            y_velocity = -y_velocity;
        }
        else if (getX(ball) + CIRCUMFERENCE >= getWidth(window))
        {
            x_velocity = -x_velocity;
        }
        else if (getX(ball) <= 0)
        {
            x_velocity = -x_velocity;
        }

        // has the ball collided with any objects ?
        GObject object = detectCollision(window, ball);
        if (object == paddle)
        {
            y_velocity = -y_velocity;
            x_velocity = drand48() * VELOCITY;
        } 
        else if (object != NULL && (strcmp(getType(object), "GRect") == 0))
        {
            // remove brick
            y_velocity = -y_velocity;
            removeGWindow(window, object);

            // update points
            points++;

            // update the scoreboard
            char s[3];
            sprintf(s, "%i", points);
            setLabel(scoreboard, s);
        }

        // linger before moving again
        pause(10);

        // check for a mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if a mouse event is detected
        if (event != NULL)
        {
            // if the event was movement of the mouse
            if (getEventType(event) == MOUSE_MOVED)
            {
                double paddle_x;
                double paddle_y = getY(paddle);

                // if the paddle is against the left side of the window:
                // - add the width of the paddle to its x location
                // else 
                // - subtract the width for the right side.
                if (getX(event) <= PADDLE_WIDTH)
                {
                    paddle_x = getX(event);
                }
                else
                {
                    paddle_x = getX(event) - getWidth(paddle);

                }

                setLocation(paddle, paddle_x, paddle_y);
            }

            // if the game has not started and the event was clicking of the mouse
            if (!game_started && getEventType(event) == MOUSE_CLICKED)
            {
                x_velocity = drand48() * VELOCITY;
                y_velocity = VELOCITY;
                game_started = true;
            }
        }

    }

    // wait for click before exiting
    waitForClick();

    // game over
    return 0;
}

/**
 * Move the ball.
 */
void moveBall(GWindow window, GOval ball, double velocity)
{
    // move ball along x axis
    move(ball, velocity, 0);

    // - bounce off right edge of window
    // - bounce off left edge of window
    if (getX(ball) + CIRCUMFERENCE >= getWidth(window))
    {   
        velocity = -velocity;
    }
    else if (getX(ball) <= 0)
    {
        velocity = -velocity;
    }

    // linger before moving again
    pause(10);
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // intitial brick position x position
    int brick_x_location = BRICK_SPACE/2; 

    // construct the brick wall one column at a time.
    for (int i = 0; i < COLS; i++)
    {
        // initial brick y position
        int brick_y_location = BRICK_DISTANCE_TOP; 

        for (int j = 0; j < ROWS; j++)
        {
            // instantiate a brick
            // - place the brick under the last one.
            GRect brick = newGRect(brick_x_location, brick_y_location, 
                BRICK_WIDTH, BRICK_HEIGHT);
            setColor(brick, brick_colors[j]);
            setFilled(brick, true);
            add(window, brick);

            // calculate next y location
            brick_y_location = brick_y_location + BRICK_HEIGHT + BRICK_SPACE; 
        }

        // calculate next x location
        brick_x_location = brick_x_location + BRICK_WIDTH + BRICK_SPACE; 
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // find the center of the window
    int ball_x_location = (getWidth(window) / 2) - RADIUS;
    int ball_y_location = (getHeight(window) / 2) - RADIUS;

    // instantiat ball 
    GOval ball = newGOval(ball_x_location, ball_y_location,
        CIRCUMFERENCE, CIRCUMFERENCE);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);

    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // place the paddle in the bottom middle of the game window.
    // - determine the x location
    // - determine the y location
    int paddle_x_location = (getWidth(window) - PADDLE_WIDTH) / 2; 
    int paddle_y_location = getHeight(window) - 50; 
   
    // instantiate a paddle
    GRect paddle = newGRect(paddle_x_location, paddle_y_location, 
        PADDLE_WIDTH, PADDLE_HEIGHT);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);

    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // instantiate scroreboard
    GLabel scoreboard = newGLabel("");
    setFont(scoreboard, "SansSerif-36");
    add(window, scoreboard);

    // update label
    char s[3];
    sprintf(s, "%i", 0);
    setLabel(scoreboard, s);

    // center and place the label
    double x = (getWidth(window) - getWidth(scoreboard)) / 2;
    double y = (getHeight(window) - getHeight(scoreboard)) / 2;
    setLocation(scoreboard, x, y);

    return scoreboard;
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
