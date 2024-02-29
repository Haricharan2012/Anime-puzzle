#include "raylib.h"
#include "stdio.h"
// #include "emscripten.h"
#define MAX_INPUT_CHARS 6
#define NONEA 6

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
Vector2 boxx[10] = {{200, 56}, {320, 56}, {440, 56}, {200, 176}, {320, 176}, {440, 176}, {200, 296}, {320, 296}, {440, 296}};
Vector2 temboxx[10] = {{200, 56}, {320, 56}, {440, 56}, {200, 176}, {320, 176}, {440, 176}, {200, 296}, {320, 296}, {440, 296}};
Vector2 mousepos = {-100.0f, 100.0f};
Vector2 temp;
Texture2D temp1;

void SaveTextToFile(const char *filePath, const char *text)
{
  FILE *file = fopen(filePath, "w");
  if (file != NULL)
  {
    fputs(text, file);
    fclose(file);
    printf("Text saved to %s\n", filePath);
  }
  else
  {
    printf("Failed to save text to %s\n", filePath);
  }
}

static int score = 0;
bool collision[70] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
int main(void)
{
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  InitAudioDevice();
  SetTargetFPS(60);
  int screenUpperLimit = 40;
  int framecounter = 0; // Set our game to run at 60 frames-per-second
                        //--------------------------------------------------------------------------------------

  // input box//
  char name[MAX_INPUT_CHARS + 1] = "\0"; // NOTE: One extra space required for null terminator char '\0'
  int letterCount = 0;
  SetTargetFPS(60);
  // int screenUpperLimit = 40;

  Rectangle textBox = {screenWidth / 2.0f - 100, 180, 225, 50};
  Rectangle dumbox = {screenWidth / 2.0f - 100, 180, 225, 50};

  bool mouseOnText = false;
  // input box//

  // textures//
  Texture2D box[10] = {LoadTexture("./puzz/box1.png"), LoadTexture("./puzz/box2.png"), LoadTexture("./puzz/box3.png"), LoadTexture("./puzz/box4.png"), LoadTexture("./puzz/box5.png"), LoadTexture("./puzz/box6.png"), LoadTexture("./puzz/box7.png"), LoadTexture("./puzz/box8.png"), LoadTexture("./puzz/box9.png")};
  Texture2D tox[10] = {LoadTexture("./puzz/dor1.png"), LoadTexture("./puzz/dor2.png"), LoadTexture("./puzz/dor3.png"), LoadTexture("./puzz/dor4.png"), LoadTexture("./puzz/dor5.png"), LoadTexture("./puzz/dor6.png"), LoadTexture("./puzz/dor7.png"), LoadTexture("./puzz/dor8.png"), LoadTexture("./puzz/dor9.png")};
  Texture2D gamesc = LoadTexture("./puzz/bs4.png");
  Texture2D nox[10] = {LoadTexture("./puzz/nar1.png"), LoadTexture("./puzz/nar2.png"), LoadTexture("./puzz/nar3.png"), LoadTexture("./puzz/nar4.png"), LoadTexture("./puzz/nar5.png"), LoadTexture("./puzz/nar6.png"), LoadTexture("./puzz/nar7.png"), LoadTexture("./puzz/nar8.png"), LoadTexture("./puzz/nar9.png")};

  Texture2D logo = LoadTexture("./puzz/logo.png");
  Texture2D screen1 = LoadTexture("./puzz/ap.png");
  Texture2D screen3 = LoadTexture("./puzz/go.png");
  Texture2D logsc = LoadTexture("./puzz/fin.png");
  Texture2D plbutton = LoadTexture("./puzz/BUTTON.png");
  Texture2D subutton = LoadTexture("./puzz/submit.png");
  Texture2D endbutton = LoadTexture("./puzz/endbut.png");
  Texture2D savebutton = LoadTexture("./puzz/savebutt.png");
  Texture2D nextbut = LoadTexture("./puzz/nextbut.png");
  Texture2D xnextbut = LoadTexture("./puzz/xnextbut.png");
  char tempx;
  // char swap[MAX_INPUT_CHARS] = "\0";
  char none[NONEA] = "\0";
  int prr = 0;
  void *ptr = &score;
  char scores;
  Sound gamesound = LoadSound("./puzz/gamemusic.mp3");

  // vectors//
  // Vector2 boxx[1]={box[0].x+110,screenHeight/8};

  // Vector2 boxx[3]={600,176};

  // constraint//
  //  for(int i=0;i<10;i++)
  //  {

  // if ((boxx[i].y + box[i].height) >= GetScreenHeight())
  //  boxx[i].y = GetScree
  // nHeight() - box[i].height;
  // else if (boxx[i].y <= screenHeight)
  //  boxx[i].y = (float)screenHeight;
  //  }
  // constraint//

  // rectangles//
  Rectangle tile1;
  Rectangle tile2;
  Rectangle tile3;
  Rectangle tile4;
  Rectangle tile5;
  Rectangle tile6;
  Rectangle tile7;
  Rectangle tile8;
  Rectangle tile9;

  Rectangle point;
  Rectangle plrect;
  Rectangle surct;
  Rectangle enrect;
  Rectangle svrect;
  Rectangle nexrect;
  Rectangle xnextrect;

  // const char *textToSave = "0";
  // const char *filename = "saved_text.txt";

  const char *textToSave = "0";
  const char *directoryPath = "/home/hari/Desktop/puzzle/"; // Replace this with the actual directory path
  const char *filename = "saved_text.txt";

  // Combine directory path and filename to create the full file path
  char fullPath[256];
  snprintf(fullPath, sizeof(fullPath), "%s%s", directoryPath, filename);

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    tile1.x = boxx[0].x;
    tile1.y = boxx[0].y;
    tile1.width = box[0].width - 50; //-50
    tile1.height = box[0].height - 25;
    tile2.x = boxx[1].x;
    tile2.y = boxx[1].y;
    tile2.width = box[1].width - 50;
    tile2.height = box[1].height - 25;
    tile3.x = boxx[2].x;
    tile3.y = boxx[2].y;
    tile3.width = box[2].width - 50;
    tile3.height = box[2].height - 25;
    tile4.x = boxx[3].x;
    tile4.y = boxx[3].y;
    tile4.width = box[3].width - 50;
    tile4.height = box[3].height - 25;

    tile5.x = boxx[4].x;
    tile5.y = boxx[4].y;
    tile5.width = box[4].width - 50;
    tile5.height = box[4].height - 25;

    tile6.x = boxx[5].x;
    tile6.y = boxx[5].y;
    tile6.width = box[5].width - 50;
    tile6.height = box[5].height - 25;

    tile7.x = boxx[6].x;
    tile7.y = boxx[6].y;
    tile7.width = box[6].width - 50;
    tile7.height = box[6].height - 25;

    tile8.x = boxx[7].x;
    tile8.y = boxx[7].y;
    tile8.width = box[7].width - 50;
    tile8.height = box[7].height - 25;

    tile9.x = boxx[8].x;
    tile9.y = boxx[8].y;
    tile9.width = box[8].width - 50;
    tile9.height = box[8].height - 25;
    point.x = mousepos.x;
    point.y = mousepos.y;
    point.width = 10;
    point.height = 10;
    plrect.width = plbutton.width;
    plrect.height = plbutton.height;
    plrect.x = 500;
    plrect.y = 350;
    surct.width = subutton.width;
    surct.height = subutton.height;
    surct.x = 400;
    surct.y = 300;
    enrect.width = endbutton.width;
    enrect.height = endbutton.height;
    enrect.x = 600;
    enrect.y = 300;
    svrect.x = 600;
    svrect.y = 200;
    svrect.width = savebutton.width;
    svrect.height = savebutton.height;

    nexrect.x = 600;
    nexrect.y = 100;

    xnextrect.x = 600;
    xnextrect.y = 100;
    nexrect.width = nextbut.width;
    nexrect.height = nextbut.height;

    mousepos = GetMousePosition();

    textToSave = TextFormat("%04i", score);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Press S to save text to file.", 10, 10, 20, DARKGRAY);
    DrawText(textToSave, 10, 50, 20, BLACK);
    const char *append = "test";
    int *pos = (int *)25;
    int io = 24;

    // Save text to file when 'S' is pressed
    if (IsKeyPressed(KEY_S))
    {

      // SaveTextToFile(fullPath, textToSave);
      SaveFileText("ssd_text.txt", "100");
      TextAppend("win", append, pos);
    }

    //        if (IsKeyDown(KEY_ENTER))
    collision[34] = (CheckCollisionRecs(point, plrect));
    if (collision[34])
    {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {

        screen1.width = 0;
        screen1.height = 0;
        plbutton.width = 0;
        plbutton.height = 0;
        // char none[NONEA] = " ";
        tempx = none[NONEA];
        none[NONEA] = name[MAX_INPUT_CHARS];
        name[MAX_INPUT_CHARS] = tempx;

        // temp=backx[0];
        // backx[0]=backx[1];
        // backx[1]=temp;
      }
    }
    collision[46] = CheckCollisionRecs(point, enrect);
    if (collision[46])
    {

      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {

        // if (IsKeyPressed(KEY_EQUAL))
        {
          for (int i = 0; i <= 10; i++)
          {

            box[i].width = 0;
            box[i].height = 0;
          }
          gamesc.width = 0;
          gamesc.height = 0;
          endbutton.width = 0;
          endbutton.height = 0;
        }
      }
    }

    collision[48] = CheckCollisionRecs(point, enrect);
    if (collision[48])
    // if (IsKeyDown(KEY_RIGHT_SHIFT))
    {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {
        screen1.width = 800;
        screen1.height = 500;
        for (int i = 0; i < 10; i++)
        {
          box[i].width = 124;
          box[i].height = 123;
          score = 0;
        }
        gamesc.width = 800;
        gamesc.height = 500;
        logsc.width = 800;
        logsc.height = 500;
        gamesc.width = 800;
        gamesc.height = 500;
        endbutton.width = 158;
        endbutton.height = 50;
        textBox.width = dumbox.width;
        textBox.height = dumbox.height;

        subutton.width = 150;
        subutton.height = 50;
        plbutton.width = 150;
        plbutton.height = 50;
        tempx = name[MAX_INPUT_CHARS];
        name[MAX_INPUT_CHARS] = none[NONEA];
        none[NONEA] = tempx;
        dumbox.x = textBox.x;
        dumbox.y = textBox.y;

        // box[i].width=800;
        // box[i].height=500;
        /// logo.width=800;
        /// logo.height=500;
      }
    }

    collision[45] = CheckCollisionRecs(surct, point);
    // if(collision[45])
    if ((collision[45] == true))
    {
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
      // if (IsKeyDown(KEY_SPACE))
      {
        logsc.width = 0;
        logsc.height = 0;
        textBox.width = 0;
        textBox.height = 0;
        dumbox.x = 315;
        dumbox.y = 12;
        subutton.height = 0;
        subutton.width = 0;
      }
    }

    if (IsKeyDown(KEY_N))
    {
      // emscripten_run_script("alert('calling js from c')");
    }
    // EM_JS(void, call_alert, (), {
    // alert('hello world!');
    //  throw 'all done';
    //  });

    if (IsKeyDown(KEY_K))
    {
      // emscripten_run_script(TextFormat("%04i",score));
      // emscripten_run_script("alert()");
      // emscripten_run_script("function dbs()");
      // emscripten_run_script("localStorage.setItem('score',goal)");
      // emscripten_idb_store("scoreboard", "scores", ptr, 8, &prr);

      // call_alert();
      // return 0;

      // EM_JS({console.log('I received: ' + $0);}, score);
    }
    if (IsKeyDown(KEY_H))
    {
      // emscripten_run_script(" hola.call()");
    }
    collision[49] = CheckCollisionRecs(point, svrect);
    if (collision[49])
    {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {
        DrawText("hello hari", 700, 300, 50, RED);
        score += 12;
        // if (IsKeyPressed(KEY_TAB))
        {

          //  emscripten_run_script("dbs.call()");
        }
      }
    }
    collision[52] = CheckCollisionRecs(point, nexrect);
    if (collision[52])
    {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {

        box[0] = tox[4];
        box[1] = tox[8];
        box[2] = tox[7];
        box[3] = tox[6];
        box[4] = tox[0];
        box[5] = tox[5];
        box[6] = tox[3];
        box[7] = tox[2];
        box[8] = tox[1];
        nextbut.width = 0;
        nextbut.height = 0;
        xnextrect.width = xnextbut.width;
        xnextrect.height = xnextbut.height;
      }
    }

    collision[53] = CheckCollisionRecs(point, xnextrect);
    if (collision[53])
    {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {
        box[0] = nox[4];
        box[1] = nox[8];
        box[2] = nox[7];
        box[3] = nox[6];
        box[4] = nox[0];
        box[5] = nox[5];
        box[6] = nox[3];
        box[7] = nox[2];
        box[8] = nox[1];
      }
    }

    // emscripten_run_script( )

    // here you can write inline javascript code!
    // console.log("(1) I have been printed from inline JavaScript!");

    // emscripten_run_script("function dbs() { (alert('fireee'))}");

    // input box//
    if (CheckCollisionPointRec(GetMousePosition(), textBox))
      mouseOnText = true;
    else
      mouseOnText = false;

    if (mouseOnText)
    {
      // Set the window's cursor to the I-Beam
      SetMouseCursor(MOUSE_CURSOR_IBEAM);

      // Get char pressed (unicode character) on the queue
      int key = GetCharPressed();

      // Check if more characters have been pressed on the same frame
      while (key > 0)
      {
        // NOTE: Only allow keys in range [32..125]
        if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
        {
          name[letterCount] = (char)key;
          name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
          letterCount++;
        }

        key = GetCharPressed(); // Check next character in the queue
      }

      if (IsKeyPressed(KEY_BACKSPACE))
      {
        letterCount--;
        if (letterCount < 0)
          letterCount = 0;
        name[letterCount] = '\0';
      }
    }
    else
      SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    //  if (mouseOnText) framecounter++;
    // else framecounter = 0;

    // inputbox//

    BeginDrawing();
    if ((boxx[0].x + box[0].width) >= GetScreenWidth() - 200)
      boxx[0].x = GetScreenWidth() - 200 - box[0].width;
    else if (boxx[0].x <= 0)
      boxx[0].x = 0;

    if ((boxx[0].y + box[0].height) >= GetScreenHeight() - 45)
      boxx[0].y = GetScreenHeight() - 45 - box[0].height;
    else if (boxx[0].y <= 0)
      boxx[0].y = 0;

    ClearBackground(RAYWHITE);

    // box[0]=GetMousePosition();
    collision[1] = CheckCollisionRecs(point, tile2);
    if (collision[1])
    {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {

        temp1 = box[1];
        box[1] = box[2];
        box[2] = temp1;
      }
      else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
      {
        temp1 = box[1];
        box[1] = box[4];
        box[4] = temp1;
      }
    }

    collision[0] = CheckCollisionRecs(point, tile1);
    if (collision[0])
    {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {

        temp1 = box[0];
        box[0] = box[1];
        box[1] = temp1;
      }
      else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
      {
        temp1 = box[0];
        box[0] = box[3];
        box[3] = temp1;
      }

      {

        // boxx[0]=mousepos;
        DrawText("hola", 0.0, 2.0f, 50, GREEN);

        // box[0]=GetMousePosition();
        // boxx[1]=GetMousePosition();
      }
    }

    collision[4] = CheckCollisionRecs(point, tile3);
    if (collision[4])
    {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {

        temp1 = box[2];
        box[2] = box[1];
        box[1] = temp1;
      }
      else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
      {
        temp1 = box[2];
        box[2] = box[5];
        box[5] = temp1;
      }
    }

    collision[9] = CheckCollisionRecs(point, tile4);
    if (collision[9])
    {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {

        temp1 = box[3];
        box[3] = box[4];
        box[4] = temp1;
      }
      else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
      {
        temp1 = box[3];
        box[3] = box[6];
        box[6] = temp1;
      }
    }

    collision[10] = CheckCollisionRecs(point, tile5);
    if (collision[10])
    {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {

        temp1 = box[4];
        box[4] = box[5];
        box[5] = temp1;
      }
      else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
      {
        temp1 = box[4];
        box[4] = box[7];
        box[7] = temp1;
      }
    }

    collision[11] = CheckCollisionRecs(point, tile6); // 11
    if (collision[11])
    {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {

        temp1 = box[5];
        box[5] = box[4];
        box[4] = temp1;
      }
      else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
      {
        temp1 = box[5];
        box[5] = box[8];
        box[8] = temp1;
      }
    }

    collision[16] = CheckCollisionRecs(point, tile7);
    if (collision[16])
    {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {
        temp1 = box[6];
        box[6] = box[7];
        box[7] = temp1;
      }
      else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
      {
        temp1 = box[6];
        box[6] = box[3];
        box[3] = temp1;
      }
    }

    collision[18] = CheckCollisionRecs(point, tile9);
    if (collision[18])
    {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {
        temp1 = box[8];
        box[8] = box[7];
        box[7] = temp1;
      }
      else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
      {
        temp1 = box[8];
        box[8] = box[5];
        box[5] = temp1;
      }
    }
    collision[17] = CheckCollisionRecs(point, tile8);
    if (collision[17])
    {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {
        none[NONEA];

        temp1 = box[7];
        box[7] = box[8];
        box[8] = temp1;
      }
      else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
      {
        temp1 = box[7];
        box[7] = box[4];
        box[4] = temp1;
      }
    }

    if (IsKeyPressed(KEY_LEFT_SHIFT))
    {

      box[0] = tox[4];
      box[1] = tox[8];
      box[2] = tox[7];
      box[3] = tox[6];
      box[4] = tox[0];
      box[5] = tox[5];
      box[6] = tox[3];
      box[7] = tox[2];
      box[8] = tox[1];
    }
    if (IsKeyPressed(KEY_LEFT_CONTROL))
    {
      box[0] = nox[4];
      box[1] = nox[8];
      box[2] = nox[7];
      box[3] = nox[6];
      box[4] = nox[0];
      box[5] = nox[5];
      box[6] = nox[3];
      box[7] = nox[2];
      box[8] = nox[1];
    }

    // downwards//

    // 3rd column

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      score += 0;
    }

    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
      score += 458;
    }
    else if (IsGestureDetected(GESTURE_SWIPE_UP))
    {
      score += 0;
    }
    else if (IsGestureDetected(GESTURE_SWIPE_DOWN))
    {
      score += 0;
    }
    // name[MAX_INPUT_CHARS] = none[NONEA];

    DrawText("prototype", 190, 200, 20, LIGHTGRAY);

    DrawTexture(screen3, screenWidth / 200, screenHeight / 200, WHITE);
    DrawTexture(gamesc, screenWidth / 800, screenHeight / 800, WHITE);

    DrawTextureV(box[0], boxx[0], WHITE);
    DrawTextureV(box[1], boxx[1], WHITE);
    DrawTextureV(box[2], boxx[2], WHITE);
    DrawTextureV(box[3], boxx[3], WHITE);
    DrawTextureV(box[4], boxx[4], WHITE);
    DrawTextureV(box[5], boxx[5], WHITE);
    DrawTextureV(box[6], boxx[6], WHITE);
    DrawTextureV(box[7], boxx[7], WHITE);
    DrawTextureV(box[8], boxx[8], WHITE);
    DrawRectangleRec(tile1, BLANK); // or
    DrawRectangleRec(tile2, BLANK); // bl
    DrawRectangleRec(tile3, BLANK); // VI
    DrawRectangleRec(tile4, BLANK); // OR
    DrawRectangleRec(tile5, BLANK); // BL
    DrawRectangleRec(tile6, BLANK); // VI
    DrawRectangleRec(tile7, BLANK); // OR
    DrawRectangleRec(tile8, BLANK); // BLUE
    DrawRectangleRec(tile9, BLANK); // VI
    DrawRectangleRec(point, BLANK); // BL
    DrawTexture(savebutton, 600, 200, WHITE);
    DrawTexture(endbutton, 600, 300, WHITE);
    DrawTexture(xnextbut, 600, 100, WHITE);
    DrawTexture(nextbut, 600, 100, WHITE);
    DrawRectangleRec(enrect, BLANK);

    DrawText(TextFormat("%04i", score), 200, 15, 45, GRAY);
    // DrawText(name,315,15,45,BLUE);
    DrawText("TURNS:", 25, 15, 45, RED);

    // DrawTexture(logo,screenWidth / 265, screenHeight / 255,WHITE);
    // DrawTexture(screen1,screenWidth / 265, screenHeight / 255,WHITE);
    DrawTexture(logsc, screenWidth / 200, screenHeight / 200, WHITE);
    DrawTexture(subutton, 400, 300, WHITE);
    DrawRectangleRec(surct, BLANK);
    // input box//
    // DrawText("Enter your name", 280, 140, 30, GREEN);
    DrawRectangleRec(dumbox, BLANK);
    DrawRectangleRec(textBox, LIGHTGRAY);
    if (mouseOnText)
      DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
    else
      DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

    DrawText(name, (int)dumbox.x + 5, (int)dumbox.y + 2, 45, BLUE);

    // DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, GREEN);

    if (mouseOnText)
    {
      if (letterCount < MAX_INPUT_CHARS)
      {
        // Draw blinking underscore char
        if (((framecounter / 20) % 2) == 0)
          DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
      }
      else
        DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
    }
    // input box//
    DrawTexture(screen1, screenWidth / 200, screenHeight / 200, WHITE);
    DrawTexture(plbutton, 500, 350, WHITE);
    DrawRectangleRec(plrect, BLANK);
    DrawTexture(logo, screenWidth / 200, screenHeight / 200, WHITE);

    framecounter++;

    if (IsKeyDown(KEY_W))
    {
      PlaySound(gamesound);
      // StopMusicStream(gamesound);
    }

    if (framecounter > 180)
    {
      logo.height = 0;
      logo.width = 0;
    }

    // DrawTextureV(box[6],boxx[4],WHITE);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  CloseAudioDevice();

  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
