#include <GL/gl.h>

#include "border.h"

void drawBorderWithOffset(int width, int height, float borderPercentage, float offsetPercentage, GLfloat *color)
{
    // Border thickness based on the percentage of the width/height
    int borderWidth = (int)(width * borderPercentage);   // Border width as a percentage of the screen width
    int borderHeight = borderWidth;

    // Offset based on the percentage of the width/height
    int offsetX = (int)(width * offsetPercentage);  // Horizontal offset from the screen edge
    int offsetY = offsetX;

    // Set the clear color based on the color parameter
    glClearColor(color[0], color[1], color[2], color[3]);

    // Left side (borderWidth wide from top to bottom, starting from the left edge with offset)
    glScissor(offsetX, offsetY, borderWidth,
              height - 2 * offsetY); // X = offsetX, Y = offsetY, Width = borderWidth, Height = (height - 2 * offsetY)
    glClear(GL_COLOR_BUFFER_BIT);

    // Right side (borderWidth wide from top to bottom, starting from the right edge with offset)
    glScissor(width - borderWidth - offsetX, offsetY, borderWidth,
              height -
                  2 * offsetY); // X = (width - borderWidth - offsetX), Y = offsetY, Width = borderWidth, Height = (height - 2 * offsetY)
    glClear(GL_COLOR_BUFFER_BIT);

    // Top side (borderHeight wide from left to right, starting from the top edge with offset)
    glScissor(offsetX, offsetY, width - 2 * offsetX,
              borderHeight); // X = offsetX, Y = offsetY, Width = (width - 2 * offsetX), Height = borderHeight
    glClear(GL_COLOR_BUFFER_BIT);

    // Bottom side (borderHeight wide from left to right, starting from the bottom edge with offset)
    glScissor(offsetX, height - borderHeight - offsetY, width - 2 * offsetX,
              borderHeight); // X = offsetX, Y = (height - borderHeight - offsetY), Width = (width - 2 * offsetX), Height = borderHeight
    glClear(GL_COLOR_BUFFER_BIT);
}

void drawGameBorder(int width, int height, float whiteBorderPercentage, float blackBorderPercentage)
{
    // Store the old clear colour
    GLfloat originalClearColour[4];
    glGetFloatv(GL_COLOR_CLEAR_VALUE, originalClearColour);

    GLfloat blackColour[4] = {0.0, 0.0, 0.0, 0.0};
    GLfloat whiteColour[4] = {1.0, 1.0, 1.0, 0.0};

    glEnable(GL_SCISSOR_TEST);

    drawBorderWithOffset(width, height, whiteBorderPercentage, blackBorderPercentage, whiteColour);
    drawBorderWithOffset(width, height, blackBorderPercentage, 0, blackColour);

    glDisable(GL_SCISSOR_TEST);

    glClearColor(originalClearColour[0], originalClearColour[1], originalClearColour[2], originalClearColour[3]);
}