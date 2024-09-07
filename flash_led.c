#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main() {
    FILE *trigger = fopen("/sys/class/leds/beaglebone:green:usr3/trigger", "w");
    FILE *brightness = fopen("/sys/class/leds/beaglebone:green:usr3/brightness", "w");
    FILE *time_diff_file = fopen("time_diff_file.txt", "w");
    struct timespec start, end;
    long long duration; // Duration in nanoseconds
    int on = 0; // Track the state of the LED

    if (trigger == NULL || brightness == NULL || time_diff_file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Disable automatic LED control
    fprintf(trigger, "none\n");
    fclose(trigger);

    printf("LED Flash Start\n"); // Output start message

    for (int i = 0; i < 1000; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start); // Time measurement start

        on = !on; // Toggle LED state
        fprintf(brightness, "%d\n", on); // Apply the new state
        fflush(brightness);

        usleep(500000); // Wait for half a second (500 milliseconds)

        clock_gettime(CLOCK_MONOTONIC, &end); // Time measurement end
        duration = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
        
        // Log only the toggle duration
        fprintf(time_diff_file, "%lld\n", duration);
        fflush(time_diff_file);
    }

    printf("LED Flash End\n"); // Output end message

    // Cleanup
    fclose(brightness);
    fclose(time_diff_file);

    return 0;
}
