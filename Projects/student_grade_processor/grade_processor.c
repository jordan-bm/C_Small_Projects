#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100
#define MAX_LINE_LEN 256
#define ASSIGN_WEIGHT 0.4f
#define MIDTERM_WEIGHT 0.3f
#define FINAL_WEIGHT 0.3f
#define GRADE_COUNT 7 // A, B, B+, C, C+, D, F

typedef struct {
    char name[MAX_NAME_LEN];
    float assignment;
    float midterm;
    float final;
    float percentage;
    char letter_grade[3];
} Student;

// Function declarations
Student* read_students(const char* filename, int* count);
void calculate_grades(Student* students, int count);
void calculate_statistics(Student* students, int count, float* avg_assign, float* avg_mid, float* avg_final, int* grade_counts);
void print_console_output(int total_students, int* grade_counts);
void write_final_file(Student* students, int count, float avg_assign, float avg_mid, float avg_final, int* grade_counts);
const char* get_letter_grade(float percentage);
int get_grade_index(const char* grade);

int main() {
    int student_count = 0;
    Student* students = read_students("students.csv", &student_count);

    if (!students) {
        fprintf(stderr, "Failed to read student data\n");
        return EXIT_FAILURE;
    }

    calculate_grades(students, student_count);
    

    float avg_assign = 0.0f, avg_mid = 0.0f, avg_final = 0.0f;
    int grade_counts[GRADE_COUNT] = {0};

    calculate_statistics(students, student_count, &avg_assign, &avg_mid, &avg_final, grade_counts);

    print_console_output(student_count, grade_counts);
    write_final_file(students, student_count, avg_assign, avg_mid, avg_final, grade_counts);

    free(students);
    return EXIT_SUCCESS;
}

// Reads CSV file student data
Student* read_students(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }
    
    Student* students = NULL;
    char line[MAX_LINE_LEN];
    *count = 0;

    while (fgets(line, sizeof(line), file)) {
        // Skip any empty lines
        if (strspn(line, " \t\n") == strlen(line)) continue;

        // Create a copy that can be modified
        char* line_copy = strdup(line);
        if (!line_copy) {
            perror("Memory error");
            fclose(file);
            free(students);
            return NULL;
        }

        // Parse field
        char* tokens[4];
        int token_count = 0;
        char* token = strtok(line_copy, ",\n");

        while (token && token_count < 4) {
            tokens[token_count++] = token;
            token = strtok(NULL, ",\n");
        }

        // Check field count
        if (token_count != 4) {
            fprintf(stderr, "Invalid format in line: %s", line);
            free(line_copy);
            continue;
        }
    
        // Create student structure
        Student s;
        strncpy(s.name, tokens[0], MAX_NAME_LEN - 1);
        s.name[MAX_NAME_LEN - 1] = '\0';

        // Validate grades
        char* endptr;
        s.assignment = strtof(tokens[1], &endptr);
        if (*endptr || s.assignment < 0 || s.assignment > 100) {
            fprintf(stderr, "Invalid assignment grade: %s\n", tokens[1]);
            free(line_copy);
            continue;
        }

        s.midterm = strtof(tokens[2], &endptr);
        if (*endptr || s.midterm < 0 || s.midterm > 100) {
            fprintf(stderr, "Invalid midterm grade: %s\n", tokens[2]);
            free(line_copy);
            continue;
        }

        s.final = strtof(tokens[3], &endptr);
        if (*endptr || s.final < 0 || s.final > 100) {
            fprintf(stderr, "Invalid final grade: %s\n", tokens[3]);
            free(line_copy);
            continue;
        }

        // Add to dynamic array
        Student* temp = realloc(students, (*count + 1) * sizeof(Student));
        if (!temp) {
            perror("Memory allocation failed");
            free(line_copy);
            fclose(file);
            free(students);
            return NULL;
        }
        students = temp;
        students[(*count)++] = s;
        free(line_copy);
    }

    fclose(file);
    return students;
}

// Calculate percentage + letter grades
void calculate_grades(Student* students, int count) {
    for (int i = 0; i < count; i++) {
        students[i].percentage = students[i].assignment * ASSIGN_WEIGHT + 
                                students[i].midterm * MIDTERM_WEIGHT +
                                students[i].final * FINAL_WEIGHT;
        const char* grade = get_letter_grade(students[i].percentage);
        strncpy(students[i].letter_grade, grade, sizeof(students[i].letter_grade)-1);
        students[i].letter_grade[sizeof(students[i].letter_grade)-1] = '\0';
    }
}

// Determines letter grade from %
const char* get_letter_grade(float percentage) {
    if (percentage >= 90.0f) return "A";
    if (percentage >= 85.0f) return "B+";
    if (percentage >= 80.0f) return "B";
    if (percentage >= 75.0f) return "C+";
    if (percentage >= 70.0f) return "C";
    if (percentage >= 60.0f) return "D";
    return "F";
}

// Returns index into grade_counts
int get_grade_index(const char* grade) {
    if (strcmp(grade, "A") == 0) return 0;
    if (strcmp(grade, "B+") == 0) return 1;
    if (strcmp(grade, "B") == 0) return 2;
    if (strcmp(grade, "C+") == 0) return 3;
    if (strcmp(grade, "C") == 0) return 4;
    if (strcmp(grade, "D") == 0) return 5;
    return 6; // F
}

// Averages anc counts per-grade
void calculate_statistics(Student* students, int count, float* avg_assign, float* avg_mid, float* avg_final, int* grade_counts) {
    float total_assign = 0, total_mid = 0, total_final = 0;

    for (int i = 0; i < count; i++) {
        total_assign += students[i].assignment;
        total_mid += students[i].midterm;
        total_final += students[i].final;

        int index = get_grade_index(students[i].letter_grade);
        if (index >= 0 && index < GRADE_COUNT) {
            grade_counts[index]++;
        }
    }

    *avg_assign = total_assign / count;
    *avg_mid = total_mid / count;
    *avg_final = total_final / count;
}

// Output (Console)
void print_console_output(int total_students, int* grade_counts) {
    printf("\nTotal Students: %d\n\n", total_students);
    printf("Number of A's: %d\n", grade_counts[0]);
    printf("Number of B+'s: %d\n", grade_counts[1]);
    printf("Number of B's: %d\n", grade_counts[2]);
    printf("Number of C+'s: %d\n", grade_counts[3]);
    printf("Number of C's: %d\n", grade_counts[4]);
    printf("Number of D's: %d\n", grade_counts[5]);
    printf("Number of F's: %d\n", grade_counts[6]);
}

// Output to grade_info.txt
void write_final_file(Student* students, int count, float avg_assign, float avg_mid, float avg_final, int* grade_counts) {
    FILE* fp = fopen("grade_info.txt", "w");
    if (!fp) {
        perror("Unable to create output file");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %.2f %s\n", students[i].name, students[i].percentage, students[i].letter_grade);
    }

    fprintf(fp, "\nTotal Students: %d\n\n", count);
    fprintf(fp, "Average Assignments Grade: %.2f\n", avg_assign);
    fprintf(fp, "Average Midterm Exam Grade: %.2f\n", avg_mid);
    fprintf(fp, "Average Final Exam Grade: %.2f\n\n", avg_final);

    fprintf(fp, "Number of A's: %d\n", grade_counts[0]);
    fprintf(fp, "Number of B+'s: %d\n", grade_counts[1]);
    fprintf(fp, "Number of B's: %d\n", grade_counts[2]);
    fprintf(fp, "Number of C+'s: %d\n", grade_counts[3]);
    fprintf(fp, "Number of C's: %d\n", grade_counts[4]);
    fprintf(fp, "Number of D's: %d\n", grade_counts[5]);
    fprintf(fp, "Number of F's %d\n", grade_counts[6]);

    fclose(fp);
}