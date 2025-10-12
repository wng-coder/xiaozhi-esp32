#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct Application;

struct Application* Application_GetInstance(void);
void Application_Start(struct Application* app);

#ifdef __cplusplus
}
#endif
