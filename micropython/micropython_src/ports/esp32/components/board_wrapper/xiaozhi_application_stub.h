#ifndef XIAOZHI_APPLICATION_STUB_H
#define XIAOZHI_APPLICATION_STUB_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Real Application class that implements the xiaozhi Application interface
// This bridges to the actual xiaozhi application functionality
class Application {
public:
    Application();
    ~Application();
    
    // Static singleton getter - matches real xiaozhi Application
    static Application& GetInstance();
    
    // Core methods that match the real Application class
    void Start();   // Launches real xiaozhi application
    void Stop();    // Stops real xiaozhi application  
    bool IsRunning(); // Checks real application status
    
private:
    // No private members needed - using global task handle
};

#endif // XIAOZHI_APPLICATION_STUB_H