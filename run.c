#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PORT 3000

// Function to call Python script
void callPythonScript() {
    int ret = system("python3 test.py");
    printf("Python script exited with code %d\n", ret);
}

// Handler for HTTP requests
int answer_to_connection(void *cls,
                         struct MHD_Connection *connection,
                         const char *url,
                         const char *method,
                         const char *version,
                         const char *upload_data,
                         size_t *upload_data_size,
                         void **con_cls) 
{
    callPythonScript();

    const char *response_str = "C server is running!\n";
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(response_str),
                                               (void*) response_str,
                                               MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (daemon == NULL) {
        fprintf(stderr, "Failed to start server\n");
        return 1;
    }

    printf("Server running on port %d. Press Enter to stop.\n", PORT);
    getchar(); // Keep server running until Enter pressed

    MHD_stop_daemon(daemon);
    return 0;
}
