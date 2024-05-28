/*
 * flappybird.c
 *
 *  Created on: May 5, 2024
 *      Author: USER
 */

#include "flappybird.h"
#include "ssd1306/ssd1306.h"
//#include "buttons.h"
#include <stdio.h>
#include "main.h"

// Game constants
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define BIRD_SIZE 8
#define GRAVITY 0.3
#define FLAP_FORCE 4
#define PIPE_WIDTH 10
#define PIPE_SPACING 20
#define PIPE_SPEED 2

// Game variables
static int birdY;
static float birdVelY;
static int score;
static int pipeX;
static int gapY;

// Function prototypes
static void drawBird();
static void drawPipe(int x, int gapY);
static void updateGame();
static void resetGame();

void FlappyBird_Init() {
    birdY = SCREEN_HEIGHT / 2;
    birdVelY = 0;
    score = 0;
    pipeX = SCREEN_WIDTH;
    gapY = SCREEN_HEIGHT / 2;

    SSD1306_Init();
    //Buttons_Init();
}

void FlappyBird_Update() {
    // Handle user input
  if (HAL_GPIO_ReadPin(RIGHT_GPIO_Port,RIGHT_Pin) == RESET) {
    	//HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)
        birdVelY = -FLAP_FORCE; // Flap the bird
    }

    // Update game logic
    updateGame();
}

void FlappyBird_Draw() {
    // Clear the screen
    SSD1306_Fill(SSD1306_COLOR_BLACK);

    // Draw game elements
    drawBird();
    drawPipe(pipeX, gapY);

    // Display the score
    char scoreStr[10];
    sprintf(scoreStr, "Score: %d", score);
    SSD1306_GotoXY(0, 0);
    SSD1306_Puts(scoreStr, &Font_7x10, SSD1306_COLOR_WHITE);

    // Update the OLED display
    SSD1306_UpdateScreen();
}

static void drawBird() {
    SSD1306_DrawFilledRectangle(20, birdY, BIRD_SIZE, BIRD_SIZE, SSD1306_COLOR_WHITE);
}

static void drawPipe(int x, int gapY) {
    SSD1306_DrawFilledRectangle(x, 0, PIPE_WIDTH, gapY - PIPE_SPACING / 2, SSD1306_COLOR_WHITE);
    SSD1306_DrawFilledRectangle(x, gapY + PIPE_SPACING / 2, PIPE_WIDTH, SCREEN_HEIGHT - gapY - PIPE_SPACING / 2, SSD1306_COLOR_WHITE);
}

static void updateGame() {
    // Update bird's vertical position based on velocity
    birdY += birdVelY;

    // Apply gravity to the bird
    birdVelY += GRAVITY;

    // Move the pipe to the left
    pipeX -= PIPE_SPEED;

    // Check for collision with the pipe
    if ((birdY < gapY - PIPE_SPACING / 2 || birdY > gapY + PIPE_SPACING / 2) && (pipeX < 20 + BIRD_SIZE && pipeX + PIPE_WIDTH > 20)) {
        // Collision detected, reset the game
        resetGame();
    }

    // Check if the pipe has passed the bird
    if (pipeX + PIPE_WIDTH < 20 && pipeX + PIPE_WIDTH + PIPE_SPEED > 20) {
        // Increase the score
        score++;

        // Generate a new random gap position for the next pipe
        gapY = rand() % (SCREEN_HEIGHT - PIPE_SPACING) + PIPE_SPACING / 2;

        // Reset the pipe position
        pipeX = SCREEN_WIDTH;
    }

    // Check if the bird has reached the top or bottom of the screen
    if (birdY < 0 || birdY + BIRD_SIZE > SCREEN_HEIGHT) {
        // Collision detected, reset the game
        resetGame();
    }
}

static void resetGame() {
    // Reset bird's position and velocity
    birdY = SCREEN_HEIGHT / 2;
    birdVelY = 0;

    // Reset score
    score = 0;

    // Reset pipe position
    pipeX = SCREEN_WIDTH;
    gapY = SCREEN_HEIGHT / 2;
}

