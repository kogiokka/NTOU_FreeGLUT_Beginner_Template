#include <glm/glm.hpp>
#include <imgui.h>
#include <imgui_impl_glut.h>
#include <imgui_impl_opengl2.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>

static int width = 1280, height = 720;
static bool show_demo_window = true;
static float ortho_fov = 1.0f;
static glm::vec4 clear_color = glm::vec4(0.45f, 0.55f, 0.6f, 0.5f);

static void normalKeyCallback(unsigned char key, int x, int y)
{
    // Press ESC to exit the application.
    if (key == 27)
    {
        glutLeaveMainLoop();
    }

    ImGui_ImplGLUT_KeyboardFunc(key, x, y);
}

static void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const double aspect_ratio = static_cast<double>(w) / static_cast<double>(h);
    const double v_offset = ortho_fov;
    const double h_offset = v_offset * aspect_ratio;
    glOrtho(-h_offset, h_offset, -v_offset, v_offset, 0, 1.0);
}

static void drawImgui()
{
    if (show_demo_window)
    {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    static int counter = 0;
    ImGui::Begin("NTOU Computer Graphics");
    ImGui::Text("Press ESC to exit");
    ImGui::Checkbox("Demo Window", &show_demo_window);
    ImGui::SliderFloat("Field of View", &ortho_fov, 1.0f, 10.0f);
    ImGui::ColorEdit3("Background Color", &clear_color[0]);
    if (ImGui::Button("Button"))
    {
        counter++;
    }
    ImGui::SameLine();
    ImGui::Text("Clicked: %d", counter);
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
}

static void displayCallback()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    drawImgui();

    // Rendering Imgui
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();
    reshape(static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));

    // Clear screen
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw a colorful triangle
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.8f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.8f, -0.8f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.8f, -0.8f, 0.0f);
    glEnd();

    // Utah teapot.
    // glutSolidTeapot(0.5);

    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    // GLUT window initialization
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInit(&argc, argv);
#ifdef __FREEGLUT_EXT_H__
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE | GLUT_DEPTH);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(width, height);
    glutCreateWindow("GLUT Example");

    // Register callbacks
    glutDisplayFunc(displayCallback);

    // Show information
    std::cout << "OpenGL Version:        " << glGetString(GL_VERSION) << "\n"
              << "Renderer:              " << glGetString(GL_RENDERER) << "\n"
              << "Vendor:                " << glGetString(GL_VENDOR) << std::endl;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGLUT_Init();
    ImGui_ImplGLUT_InstallFuncs();
    ImGui_ImplOpenGL2_Init();

    // This line must be after ImGui_ImplGLUT_InstallFuncs().
    glutKeyboardFunc(normalKeyCallback);

    glutMainLoop();

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
    return 0;
}
