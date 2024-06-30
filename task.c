#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_TASKS 100
#define MAX_NOTIFICATIONS 100

// Enumeration for priority levels
enum Priority {
    LOW,
    MEDIUM,
    HIGH
};

// Enumeration for progress states
enum Progress {
    IN_PROGRESS,
    TODO,
    DONE
};

// Structure to represent a task
struct Task {
    char description[100];
    time_t start_date;
    time_t end_date;
    enum Priority priority;
    enum Progress progress;
};

// Structure to represent a notification
struct Notification {
    char message[100];
    time_t time;
};

// Function to parse date string and convert it to time_t
time_t parseDate(const char *dateStr) {
    struct tm tm = {0};
    sscanf(dateStr, "%4d-%2d-%2d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
    tm.tm_year -= 1900; // Adjust for year since tm_year is years since 1900
    tm.tm_mon -= 1;     // Adjust for month since tm_mon is zero-based
    return mktime(&tm);
}

// Function to add a task
void addTask(struct Task tasks[], int *task_count) {
    if (*task_count >= MAX_TASKS) {
        printf("Cannot add more tasks. Task limit reached.\n");
        return;
    }

    printf("Enter task description: ");
    fgets(tasks[*task_count].description, sizeof(tasks[*task_count].description), stdin);
    tasks[*task_count].description[strcspn(tasks[*task_count].description, "\n")] = '\0'; // remove newline character
    printf("Enter start date (YYYY-MM-DD): ");
    char startDateStr[12];
    scanf("%s", startDateStr);
    getchar(); // consume newline
    tasks[*task_count].start_date = parseDate(startDateStr);
    printf("Enter end date (YYYY-MM-DD): ");
    char endDateStr[12];
    scanf("%s", endDateStr);
    getchar(); // consume newline
    tasks[*task_count].end_date = parseDate(endDateStr);
    printf("Enter priority (1-Low, 2-Medium, 3-High): ");
    int priority_choice;
    scanf("%d", &priority_choice);
    getchar(); // consume newline
    switch (priority_choice) {
        case 1:
            tasks[*task_count].priority = LOW;
            break;
        case 2:
            tasks[*task_count].priority = MEDIUM;
            break;
        case 3:
            tasks[*task_count].priority = HIGH;
            break;
        default:
            printf("Invalid priority choice. Setting priority to LOW.\n");
            tasks[*task_count].priority = LOW;
    }
    printf("Enter progress (1-In Progress, 2-To Do, 3-Done): ");
    int progress_choice;
    scanf("%d", &progress_choice);
    getchar(); // consume newline
    switch (progress_choice) {
        case 1:
            tasks[*task_count].progress = IN_PROGRESS;
            break;
        case 2:
            tasks[*task_count].progress = TODO;
            break;
        case 3:
            tasks[*task_count].progress = DONE;
            break;
        default:
            printf("Invalid progress choice. Setting progress to In Progress.\n");
            tasks[*task_count].progress = IN_PROGRESS;
    }

    (*task_count)++;
}

// Function to display all tasks
void displayTasks(struct Task tasks[], int task_count) {
    printf("Tasks:\n");
    for (int i = 0; i < task_count; i++) {
        printf("Task %d:\n", i+1);
        printf("Description: %s\n", tasks[i].description);
        printf("Start date: %s", asctime(localtime(&tasks[i].start_date)));
        printf("End date: %s", asctime(localtime(&tasks[i].end_date)));
        printf("Priority: ");
        switch (tasks[i].priority) {
            case LOW:
                printf("Low\n");
                break;
            case MEDIUM:
                printf("Medium\n");
                break;
            case HIGH:
                printf("High\n");
                break;
        }
        printf("Progress: ");
        switch (tasks[i].progress) {
            case IN_PROGRESS:
                printf("In Progress\n");
                break;
            case TODO:
                printf("To Do\n");
                break;
            case DONE:
                printf("Done\n");
                break;
        }
        printf("\n");
    }
}

// Function to add a notification
void addNotification(struct Notification notifications[], int *notification_count, const char *message, time_t time) {
    if (*notification_count >= MAX_NOTIFICATIONS) {
        printf("Cannot add more notifications. Notification limit reached.\n");
        return;
    }
    strcpy(notifications[*notification_count].message, message);
    notifications[*notification_count].time = time;
    (*notification_count)++;
}



int main() {
    struct Task tasks[MAX_TASKS];
    struct Notification notifications[MAX_NOTIFICATIONS];
    int task_count = 0;
    int notification_count = 0;
    int choice;

    do {
        printf("1. Add Task\n");
        printf("2. Display Tasks\n");
        printf("3. Send Reminders\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                addTask(tasks, &task_count);
                break;
            case 2:
                displayTasks(tasks, task_count);
                break;
            case 3:
                printf("Please do your work and complete your tasks.\n");
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (choice != 4);

    return 0;
}
