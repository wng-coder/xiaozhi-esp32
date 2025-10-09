#ifndef XIAOZHI_LAUNCHER_H
#define XIAOZHI_LAUNCHER_H

#ifdef __cplusplus
extern "C" {
#endif

// Launch the xiaozhi application
void launch_xiaozhi_application();

// Get application status
int get_xiaozhi_status();

// Stop the application
void stop_xiaozhi_application();

#ifdef __cplusplus
}
#endif

#endif // XIAOZHI_LAUNCHER_H