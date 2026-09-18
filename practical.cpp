#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Student{
    string name;
    char section;
    int roll_no;
    string password;
    int Ai_Marks = 0;
    int OOPM_Marks = 0;
    int IPS_Marks = 0;
    int DS_Marks = 0;
    int TC_Marks = 0;
    int total = 0;
    float percentage = 0.0;
};

int loginsearch(int input_roll, string input_pass, Student arr[], int size){
    for (int i = 0; i<size; i++){
        if (arr[i].roll_no == input_roll && arr[i].password == input_pass){
         return i;
        }
    }
    return -1;
}

int searchroll(int search_roll, Student arr[], int size){
    for (int i = 0; i<size; i++){
        if (arr[i].roll_no == search_roll){
            return i;
        }
    }
    return -1;
}

int main(){
    Student sectionA[50];
    Student sectionB[50];
    
    for (int i = 0;i<50;i++){
        sectionA[i].roll_no = i + 1;
        sectionA[i].password = "stdA"+ to_string(i+1);
        sectionA[i].section = 'A';
    }
    for (int j = 0; j<50; j++){
        sectionB[j].roll_no = j + 51;
        sectionB[j].password = "stdB"+ to_string(j+1);
        sectionB[j].section = 'B';
    }
    
    ifstream inFile("practical_marks.txt");
    if (inFile.is_open()) {
        string header; 
        getline(inFile, header);
        for (int i = 0; i < 50; i++){
            inFile >> sectionA[i].roll_no >> sectionA[i].section >> sectionA[i].password 
                   >> sectionA[i].Ai_Marks >> sectionA[i].OOPM_Marks >> sectionA[i].IPS_Marks 
                   >> sectionA[i].DS_Marks >> sectionA[i].TC_Marks >> sectionA[i].total >> sectionA[i].percentage;
        }
        for (int i = 0; i < 50; i++){
            inFile >> sectionB[i].roll_no >> sectionB[i].section >> sectionB[i].password 
                   >> sectionB[i].Ai_Marks >> sectionB[i].OOPM_Marks >> sectionB[i].IPS_Marks 
                   >> sectionB[i].DS_Marks >> sectionB[i].TC_Marks >> sectionB[i].total >> sectionB[i].percentage;
        }
        inFile.close();
    }
    
    int choice;
    while (true){
        cout << "\n===========================\n";
        cout << "  STUDENT MANAGEMENT SYSTEM  \n";
        cout << "===========================\n";
        cout << "1. Teacher Portal\n";
        cout << "2. Student Portal\n";
        cout << "3. Exit & Save\n";
        cout << "4. ADMIN Portal\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        int temp_m;
        
        // ==========================================
        // CHOICE 1: TEACHER PORTAL
        // ==========================================
        if (choice == 1){
            string t_pass;
            cout << "\n--- TEACHER PORTAL ---\n";
            cout << "Enter Teacher Password: ";
            cin >> t_pass;
            
            // --- AI TEACHER ---
            if (t_pass == "admin_ai"){
                cout << "\n[ AI TEACHER LOGGED IN ]\n";
                cout << "To exit mid-input of marks, type -1.\n";
                int target_roll;
                while (true){
                    cout << "\nEnter Roll No to grade (or type -1 to exit): ";
                    cin >> target_roll;
                    if (target_roll == -1) break;
                    
                    int indexInA = searchroll(target_roll, sectionA, 50);
                    int indexInB = searchroll(target_roll, sectionB, 50);
                    
                    if (indexInA != -1){
                        cout << "Student Found: " << sectionA[indexInA].name << "\n";
                        cout << "Current AI Mark: " << sectionA[indexInA].Ai_Marks << "\n";
                        cout << "Enter new AI Mark: ";
                        cin >> temp_m;
                        if (temp_m == -1) break;
                        sectionA[indexInA].Ai_Marks = temp_m;
                        cout << "Mark updated in system.\n";
                    } else if (indexInB != -1){
                        cout << "Student Found: " << sectionB[indexInB].name << "\n";
                        cout << "Current AI Mark: " << sectionB[indexInB].Ai_Marks << "\n";
                        cout << "Enter new AI Mark: ";
                        cin >> temp_m;
                        if (temp_m == -1) break;
                        sectionB[indexInB].Ai_Marks = temp_m;
                        cout << "Mark updated in system.\n";
                    } else {
                        cout << "ERROR: Student does not exist!\n";
                    }
                }
            } // END AI TEACHER
            
            // --- OOPM TEACHER ---
            else if (t_pass == "admin_oopm"){
                cout << "\n[ OOPM TEACHER LOGGED IN ]\n";
                cout << "To exit mid-input of marks, type -1.\n";
                int target_roll;
                while (true){
                    cout << "\nEnter Roll No to grade (or type -1 to exit): ";
                    cin >> target_roll;
                    if (target_roll == -1) break;
                    
                    int indexInA = searchroll(target_roll, sectionA, 50);
                    int indexInB = searchroll(target_roll, sectionB, 50);
                    
                    if (indexInA != -1){
                        cout << "Student Found: " << sectionA[indexInA].name << "\n";
                        cout << "Current OOPM Mark: " << sectionA[indexInA].OOPM_Marks << "\n";
                        cout << "Enter new OOPM Mark: ";
                        cin >> temp_m;
                        if (temp_m == -1) break;
                        sectionA[indexInA].OOPM_Marks = temp_m;
                        cout << "Mark updated in system.\n";
                    } else if (indexInB != -1){
                        cout << "Student Found: " << sectionB[indexInB].name << "\n";
                        cout << "Current OOPM Mark: " << sectionB[indexInB].OOPM_Marks << "\n";
                        cout << "Enter new OOPM Mark: ";
                        cin >> temp_m;
                        if (temp_m == -1) break;
                        sectionB[indexInB].OOPM_Marks = temp_m;
                        cout << "Mark updated in system.\n";
                    } else {
                        cout << "ERROR: Student does not exist!\n";
                    }
                }
            } // END OOPM TEACHER
            
            // --- DS TEACHER ---
            else if (t_pass == "admin_ds"){
                cout << "\n[ DS TEACHER LOGGED IN ]\n";
                cout << "To exit mid-input of marks, type -1.\n";
                int target_roll;
                while (true){
                    cout << "\nEnter Roll No to grade (or type -1 to exit): ";
                    cin >> target_roll;
                    if (target_roll == -1) break;
                    
                    int indexInA = searchroll(target_roll, sectionA, 50);
                    int indexInB = searchroll(target_roll, sectionB, 50);
                    
                    if (indexInA != -1){
                        cout << "Student Found: " << sectionA[indexInA].name << "\n";
                        cout << "Current DS Mark: " << sectionA[indexInA].DS_Marks << "\n";
                        cout << "Enter new DS Mark: ";
                        cin >> temp_m;
                        if (temp_m == -1) break;
                        sectionA[indexInA].DS_Marks = temp_m;
                        cout << "Mark updated in system.\n";
                    } else if (indexInB != -1){
                        cout << "Student Found: " << sectionB[indexInB].name << "\n";
                        cout << "Current DS Mark: " << sectionB[indexInB].DS_Marks << "\n";
                        cout << "Enter new DS Mark: ";
                        cin >> temp_m;
                        if (temp_m == -1) break;
                        sectionB[indexInB].DS_Marks = temp_m;
                        cout << "Mark updated in system.\n";
                    } else {
                        cout << "ERROR: Student does not exist!\n";
                    }
                }
            } // END DS TEACHER
            
            // --- IPS TEACHER ---
            else if (t_pass == "admin_ips"){
                cout << "\n[ IPS TEACHER LOGGED IN ]\n";
                cout << "To exit mid-input of marks, type -1.\n";
                int target_roll;
                while (true){
                    cout << "\nEnter Roll No to grade (or type -1 to exit): ";
                    cin >> target_roll;
                    if (target_roll == -1) break;
                    
                    int indexInA = searchroll(target_roll, sectionA, 50);
                    int indexInB = searchroll(target_roll, sectionB, 50);
                    
                    if (indexInA != -1){
                        cout << "Student Found: " << sectionA[indexInA].name << "\n";
                        cout << "Current IPS Mark: " << sectionA[indexInA].IPS_Marks << "\n";
                        cout << "Enter new IPS Mark: ";
                        cin >> temp_m;
                        if (temp_m == -1) break;
                        sectionA[indexInA].IPS_Marks = temp_m;
                        cout << "Mark updated in system.\n";
                    } else if (indexInB != -1){
                        cout << "Student Found: " << sectionB[indexInB].name << "\n";
                        cout << "Current IPS Mark: " << sectionB[indexInB].IPS_Marks << "\n";
                        cout << "Enter new IPS Mark: ";
                        cin >> temp_m;
                        if (temp_m == -1) break;
                        sectionB[indexInB].IPS_Marks = temp_m;
                        cout << "Mark updated in system.\n";
                    } else {
                        cout << "ERROR: Student does not exist!\n";
                    }
                }
            } // END IPS TEACHER
            
            // --- TC TEACHER ---
            else if (t_pass == "admin_tc"){
                cout << "\n[ TC TEACHER LOGGED IN ]\n";
                cout << "To exit mid-input of marks, type -1.\n";
                int target_roll;
                while (true){
                    cout << "\nEnter Roll No to grade (or type -1 to exit): ";
                    cin >> target_roll;
                    if (target_roll == -1) break;
                    
                    int indexInA = searchroll(target_roll, sectionA, 50);
                    int indexInB = searchroll(target_roll, sectionB, 50);
                    
                    if (indexInA != -1){
                        cout << "Student Found: " << sectionA[indexInA].name << "\n";
                        cout << "Current TC Mark: " << sectionA[indexInA].TC_Marks << "\n";
                        cout << "Enter new TC Mark: ";
                        cin >> temp_m;
                        if (temp_m == -1) break;
                        sectionA[indexInA].TC_Marks = temp_m;
                        cout << "Mark updated in system.\n";
                    } else if (indexInB != -1){
                        cout << "Student Found: " << sectionB[indexInB].name << "\n";
                        cout << "Current TC Mark: " << sectionB[indexInB].TC_Marks << "\n";
                        cout << "Enter new TC Mark: ";
                        cin >> temp_m;
                        if (temp_m == -1) break;
                        sectionB[indexInB].TC_Marks = temp_m;
                        cout << "Mark updated in system.\n";
                    } else {
                        cout << "ERROR: Student does not exist!\n";
                    }
                }
            } // END TC TEACHER
            
            else {
                cout << "\nAccess Denied. Incorrect Subject Password.\n";
            }
        }
        
        // ==========================================
        // CHOICE 2: STUDENT PORTAL
        // ==========================================
        else if(choice == 2){
            int input_roll;
            string input_pass;
            cout << "\n--- STUDENT LOGIN ---\n";
            cout << "Enter Roll Number: ";
            cin >> input_roll;
            cout << "Enter Password: ";
            cin >> input_pass;
            
            int indexInA = loginsearch(input_roll, input_pass, sectionA, 50);
            int indexInB = loginsearch(input_roll, input_pass, sectionB, 50);
            
            Student* activeStudent = nullptr;
            
            if (indexInA != -1) activeStudent = &sectionA[indexInA];
            else if (indexInB != -1) activeStudent = &sectionB[indexInB];
            
            if (activeStudent != nullptr){
                activeStudent->total = activeStudent->Ai_Marks + activeStudent->OOPM_Marks + activeStudent->IPS_Marks + activeStudent->DS_Marks + activeStudent->TC_Marks;
                activeStudent->percentage = (activeStudent->total / 250.0) * 100.0;
                
                cout << "\n=======================================\n";
                cout << "           PRACTICAL MARKSHEET            \n";
                cout << "=======================================\n";
                cout << " Name:    " << activeStudent->name << "\n";
                cout << " Roll No: " << activeStudent->roll_no << " | Sec: " << activeStudent->section << "\n";
                cout << "---------------------------------------\n";
                cout << " Artificial Intelligence : " << activeStudent->Ai_Marks << " / 50\n";
                cout << " OOPM                    : " << activeStudent->OOPM_Marks << " / 50\n";
                cout << " IPS                     : " << activeStudent->IPS_Marks << " / 50\n";
                cout << " Data Structures         : " << activeStudent->DS_Marks << " / 50\n";
                cout << " Theory of Computation   : " << activeStudent->TC_Marks << " / 50\n";
                cout << "---------------------------------------\n";
                cout << " TOTAL SCORE             : " << activeStudent->total << " / 250\n";
                cout << " PERCENTAGE              : " << activeStudent->percentage << " %\n";
                cout << "=======================================\n";
            } else {
                cout << "\nAccess Denied. Wrong ID or Password.\n";
            }
        }
        
        // ==========================================
        // CHOICE 3: EXIT & SAVE
        // ==========================================
        else if (choice == 3){
            cout << "\nSaving data and generating spreadsheet...\n";
            ofstream outFile("practical_marks.txt");
            outFile << "Roll\tSec\tPass\tAI\tOOPM\tIPS\tDS\tTC\tTotal\tPercent\n";
            for (int i = 0; i < 50; i++) {
                outFile << sectionA[i].roll_no << "\t" << sectionA[i].section << "\t" 
                        << sectionA[i].password << "\t" << sectionA[i].Ai_Marks << "\t" 
                        << sectionA[i].OOPM_Marks << "\t" << sectionA[i].IPS_Marks << "\t" 
                        << sectionA[i].DS_Marks << "\t" << sectionA[i].TC_Marks << "\t" 
                        << sectionA[i].total << "\t" << sectionA[i].percentage << "\n";
            }
            for (int i = 0; i < 50; i++) {
                outFile << sectionB[i].roll_no << "\t" << sectionB[i].section << "\t" 
                        << sectionB[i].password << "\t" << sectionB[i].Ai_Marks << "\t" 
                        << sectionB[i].OOPM_Marks << "\t" << sectionB[i].IPS_Marks << "\t" 
                        << sectionB[i].DS_Marks << "\t" << sectionB[i].TC_Marks << "\t" 
                        << sectionB[i].total << "\t" << sectionB[i].percentage << "\n";
            }
            outFile.close();
            cout << "Exiting. Goodbye!\n";
            break;
        }
        
        // ==========================================
        // CHOICE 4: ADMIN PORTAL
        // ==========================================
        else if (choice == 4) {
            string admin_pass;
            int attempts = 0;
            bool access_granted = false;
            
            cout << "\n--- ADMIN PORTAL ---\n";
            while (attempts < 3) {
                cout << "Enter Master Password (Attempt " << (attempts + 1) << " of 3): ";
                cin >> admin_pass;
                
                if (admin_pass == "dev_admin") {
                    access_granted = true;
                    break; 
                } else {
                    attempts++;
                    cout << "Access Denied. Incorrect password.\n\n";
                }
            }
            
            if (access_granted == true) {
                cout << "\n========================================================================\n";
                cout << "                          MASTER DATABASE VIEW                            \n";
                cout << "========================================================================\n";
                cout << "Roll\tSec\tPass\tAI\tOOPM\tIPS\tDS\tTC\tTotal\tPercent\n";
                cout << "------------------------------------------------------------------------\n";
                
                for (int i = 0; i < 50; i++) {
                    cout << sectionA[i].roll_no << "\t" << sectionA[i].section << "\t" 
                         << sectionA[i].password << "\t" << sectionA[i].Ai_Marks << "\t" 
                         << sectionA[i].OOPM_Marks << "\t" << sectionA[i].IPS_Marks << "\t" 
                         << sectionA[i].DS_Marks << "\t" << sectionA[i].TC_Marks << "\t" 
                         << sectionA[i].total << "\t" << sectionA[i].percentage << "%\n";
                }
                for (int i = 0; i < 50; i++) {
                    cout << sectionB[i].roll_no << "\t" << sectionB[i].section << "\t" 
                         << sectionB[i].password << "\t" << sectionB[i].Ai_Marks << "\t" 
                         << sectionB[i].OOPM_Marks << "\t" << sectionB[i].IPS_Marks << "\t" 
                         << sectionB[i].DS_Marks << "\t" << sectionB[i].TC_Marks << "\t" 
                         << sectionB[i].total << "\t" << sectionB[i].percentage << "%\n";
                }
                cout << "========================================================================\n";
            } else {
                string security_email = ""; 
                cout << "[SECURITY ALERT] Maximum authentication attempts exceeded.\n";
                cout << "Triggering system lockdown... Simulating security alert email to admins.\n";
            }
        }
        
        else {
            cout << "\nInvalid choice. Please choose (1-4)!\n";
        }
    }
    return 0;
}