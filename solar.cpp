#include <graphics.h>
#include <math.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <utility>

#define SUN_RADIUS 50
#define EARTH_RADIUS 20
#define SATELLITE_RADIUS 10
#define EARTH_ORBIT_RADIUS 200
#define PI 3.14159265

// Satellite distances (in arbitrary units)
#define INSAT_ORBIT_RADIUS 30   // INSAT
#define IRS_ORBIT_RADIUS 40     // IRS
#define NAVIC_ORBIT_RADIUS 50    // NavIC

void drawSun(int x, int y) {
    setcolor(YELLOW);
    circle(x, y, SUN_RADIUS);
    floodfill(x, y, YELLOW); // Fill the sun with yellow
}

std::pair<int, int> drawEarth(int centerX, int centerY, float angle) {
    int earthX = centerX + EARTH_ORBIT_RADIUS * cos(angle);
    int earthY = centerY + EARTH_ORBIT_RADIUS * sin(angle);
    
    setcolor(BLUE);
    circle(earthX, earthY, EARTH_RADIUS);
    floodfill(earthX, earthY, BLUE); // Fill the Earth with blue
    
    return std::make_pair(earthX, earthY); // Return Earth's coordinates as a pair
}

void drawSatellite(int earthX, int earthY, float satelliteAngle, int orbitRadius, int color) {
    int satelliteX = earthX + orbitRadius * cos(satelliteAngle);
    int satelliteY = earthY + orbitRadius * sin(satelliteAngle);
    
    setcolor(color);
    circle(satelliteX, satelliteY, SATELLITE_RADIUS);
    floodfill(satelliteX, satelliteY, color); // Fill the satellite with its color
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;

    float earthAngle = 0;
    float insatAngle = 0;
    float irsAngle = 0;
    float navicAngle = 0;

    // Number of frames for animation
    int frameCount = 500;

    for (int i = 0; i < frameCount; ++i) {
        cleardevice(); // Clear the screen

        drawSun(centerX, centerY);
        std::pair<int, int> earthCoords = drawEarth(centerX, centerY, earthAngle);
        int earthX = earthCoords.first;
        int earthY = earthCoords.second;
        
        // Draw Indian satellites
        drawSatellite(earthX, earthY, insatAngle, INSAT_ORBIT_RADIUS, GREEN); // INSAT satellite
        drawSatellite(earthX, earthY, irsAngle, IRS_ORBIT_RADIUS, CYAN); // IRS satellite
        drawSatellite(earthX, earthY, navicAngle, NAVIC_ORBIT_RADIUS, MAGENTA); // NavIC satellite

        // Update angles for animation
        earthAngle += 0.01; // Increment angle for Earth
        if (earthAngle > 2 * PI) {
            earthAngle -= 2 * PI; // Keep angle within 0 to 2*PI
        }
        
        insatAngle += 0.02; // Increment angle for INSAT
        if (insatAngle > 2 * PI) {
            insatAngle -= 2 * PI; // Keep angle within 0 to 2*PI
        }
        
        irsAngle += 0.03; // Increment angle for IRS
        if (irsAngle > 2 * PI) {
            irsAngle -= 2 * PI; // Keep angle within 0 to 2*PI
        }
        
        navicAngle += 0.04; // Increment angle for NavIC
        if (navicAngle > 2 * PI) {
            navicAngle -= 2 * PI; // Keep angle within 0 to 2*PI
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Control the speed of the animation
    }

    closegraph();
    return 0;
}
