// Scenario: University Timetable Scheduling
// A university is facing challenges in scheduling exam timetables due to overlapping student 
// enrollments in multiple courses. To prevent clashes, the university needs to assign exam 
// slots efficiently, ensuring that no two exams taken by the same student are scheduled at the 
// same time. 
// To solve this, the university decides to model the problem as a Graph Coloring Problem, 
// where: 
// ● Each course is represented as a vertex. 
// ● An edge exists between two vertices if a student is enrolled in both courses. 
// ● Each vertex (course) must be assigned a color (time slot) such that no two adjacent 
// vertices share the same color (no two exams with common students are scheduled in the 
// same slot). 
// As a scheduling system developer, you must: 
// 1. Model the problem as a graph and implement a graph coloring algorithm (e.g., Greedy 
// Coloring or Backtracking). 
// 2. Minimize the number of colors (exam slots) needed while ensuring conflict-free 
// scheduling. 
// 3. Handle large datasets with thousands of courses and students, optimizing performance. 
// 4. Compare the efficiency of Greedy Coloring, DSATUR, and Welsh-Powell algorithms 
// for better scheduling. 
// Extend the solution to include room allocation constraints where exams in the same slot should 
// fit within available classrooms. 

//Shreedhar Bargaje- 123B1F006


import java.util.*;

public class Assignment7 {
    static int numCourses, numRooms;
    static boolean[][] clashMatrix;
    static int[] classSize;
    static int[] roomCapacity;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("=== University Course Scheduling System ===");
        System.out.print("Enter total number of courses: ");
        numCourses = Integer.parseInt(sc.nextLine().trim());

        System.out.print("Enter total number of rooms available: ");
        numRooms = Integer.parseInt(sc.nextLine().trim());

        classSize = new int[numCourses];
        System.out.println("\nEnter size (number of students) for each course:");
        for (int i = 0; i < numCourses; ++i)
            classSize[i] = Integer.parseInt(sc.nextLine().trim());

        roomCapacity = new int[numRooms];
        System.out.println("\nEnter capacity for each room:");
        for (int i = 0; i < numRooms; ++i)
            roomCapacity[i] = Integer.parseInt(sc.nextLine().trim());

        clashMatrix = new boolean[numCourses][numCourses];
        System.out.print("\nEnter total number of students enrolled: ");
        int totalStudents = Integer.parseInt(sc.nextLine().trim());
        System.out.println("Enter each student's course list (space-separated 0-based course IDs):");
        
        for (int s = 0; s < totalStudents; ++s) {
            String line = sc.nextLine().trim();
            if (line.isEmpty()) { s--; continue; }
            String[] parts = line.split("\\s+");
            List<Integer> enrolled = new ArrayList<>();
            for (String p : parts) enrolled.add(Integer.parseInt(p));
            for (int i = 0; i < enrolled.size(); ++i)
                for (int j = i + 1; j < enrolled.size(); ++j) {
                    int a = enrolled.get(i), b = enrolled.get(j);
                    clashMatrix[a][b] = clashMatrix[b][a] = true;
                }
        }

      
        for (int i = 0; i < numCourses; ++i) {
            boolean fits = false;
            for (int r = 0; r < numRooms; ++r)
                if (roomCapacity[r] >= classSize[i])
                    fits = true;
            if (!fits) {
                System.out.println("\nCourse " + i + " cannot fit in any available room. Scheduling aborted.");
                sc.close();
                return;
            }
        }

        boolean scheduled = false;
        int[] timeSlot = new int[numCourses];
        int[] assignedRoom = new int[numCourses];

       
        for (int k = 1; k <= numCourses && !scheduled; ++k) {
            Arrays.fill(timeSlot, -1);
            Arrays.fill(assignedRoom, -1);
            boolean[][] occupied = new boolean[k][numRooms];

            if (assignCourse(0, k, timeSlot, assignedRoom, occupied)) {
                System.out.println("\nSchedule found with " + k + " time slots:");
                for (int i = 0; i < numCourses; ++i)
                    System.out.println("Course " + i + " → Slot " + (timeSlot[i] + 1) + ", Room " + assignedRoom[i]);
                scheduled = true;
            }
        }

        if (!scheduled)
            System.out.println("\nNo valid timetable found up to " + numCourses + " time slots.");

        sc.close();
    }

    static boolean assignCourse(int idx, int totalSlots, int[] timeSlot, int[] assignedRoom, boolean[][] occupied) {
        if (idx == numCourses) return true; // All courses placed

        for (int slot = 0; slot < totalSlots; ++slot) {
            boolean clash = false;
            for (int j = 0; j < numCourses; ++j) {
                if (clashMatrix[idx][j] && timeSlot[j] == slot) {
                    clash = true;
                    break;
                }
            }
            if (clash) continue;

            for (int room = 0; room < numRooms; ++room) {
                if (occupied[slot][room]) continue;
                if (roomCapacity[room] < classSize[idx]) continue;

                timeSlot[idx] = slot;
                assignedRoom[idx] = room;
                occupied[slot][room] = true;

                if (assignCourse(idx + 1, totalSlots, timeSlot, assignedRoom, occupied))
                    return true;

                
                timeSlot[idx] = -1;
                assignedRoom[idx] = -1;
                occupied[slot][room] = false;
            }
        }
        return false;
    }
}

/*=== University Course Scheduling System ===
Enter total number of courses: 4
Enter total number of rooms available: 2

Enter size (number of students) for each course:
30
25
40
20

Enter capacity for each room:
35
50

Enter total number of students enrolled: 4
Enter each student's course list (space-separated 0-based course IDs):
0 1
1 2
2 3
0 3

Schedule found with 2 time slots:
Course 0 ? Slot 1, Room 0
Course 1 ? Slot 2, Room 0
Course 2 ? Slot 1, Room 1
Course 3 ? Slot 2, Room 1*/
