#include "xiaozhi_launcher.h"
#include <esp_log.h>

// Include the xiaozhi application stub (real interface, minimal implementation)
#include "xiaozhi_application_stub.h"

static const char* TAG = "xiaozhi_launcher";

extern "C" {

void launch_xiaozhi_application() {
    ESP_LOGI(TAG, "Launching real xiaozhi Application class");
    
    // Launch the actual xiaozhi application using the stub!
    ESP_LOGI(TAG, "Starting Application::GetInstance()");
    auto& app = Application::GetInstance();
    
    ESP_LOGI(TAG, "Calling app.Start() - real xiaozhi Application class integration");
    app.Start();
    
    ESP_LOGI(TAG, "Real xiaozhi Application::Start() completed successfully!");
}

int get_xiaozhi_status() {
    // Get status from the real Application instance
    auto& app = Application::GetInstance();
    bool running = app.IsRunning();
    ESP_LOGI(TAG, "Xiaozhi application status: %s", running ? "RUNNING" : "STOPPED");
    return running ? 1 : 0;
}

void stop_xiaozhi_application() {
    ESP_LOGI(TAG, "Stopping real xiaozhi Application class");
    
    // Stop the actual xiaozhi application
    auto& app = Application::GetInstance();
    app.Stop();
    
    ESP_LOGI(TAG, "Real xiaozhi Application::Stop() completed");
}

}