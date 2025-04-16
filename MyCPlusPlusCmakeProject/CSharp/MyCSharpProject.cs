public MyClass{
    Timer timer;
    Dictionary<string, string> monitoredProcesses

    public MyClass()
    {
        // important to give the correct process name
        monitoredProcesses = new Dictionary<string, string>()
        {
            { "notepad", "C:/Windows/System32/notepad.exe"},
            { "calculator", "C:/Windows/System32/calc.exe"}
        };

        timer = new Timer(5000);
        timer.Elapsed += checkProcess;
        timer.Start();
    }

    private void checkProcess(object sender, ElapsedEventArgs e)
    {
        foreach(var process in monitoredProcesses)
        {
            if(!IsProcessRunning(process.Key))
            {
                Console.WriteLine($"{process.Key} is down, restarting...");
                RestartApplication(process.Value);
            }
            else
            {
                Console.WriteLine($"{process.Key} is running")
            }
        }
    }

    private void RestartApplication(string processPath)
    {
        try
        {
            Process.Start(processPath);
            Console.WriteLine($"{processPath} restarted");
        }
        catch(Exception e)
        {
            Console.WriteLine($"Failed to start: {e.Message}");
        }
    }

    private bool IsProcessRunning(string processName)
    {
        /*  Searches through the process name to check if the process is running
            if the name is wrong, it will always return false   */
        bool bRet = Process.GetProcessesByName(processName).Length > 0;
        return bRet;
    }

    private bool ExecuteScript(string script, string args = null)
    {
        string baseDirectory = "{full path}";
        string fullScriptPath = Path.Combine(baseDirectory, script);

        // check if the script exist
        if(!File.Exists(fullScriptPath))
        {
            Console.WriteLine($"{script} at {fullScriptPath} does not exist");
            return;
        }

        ProcessStartInfo processInfo = new ProcessStartInfo
        {
            FileName = fullScriptPath;
            Arguments = args;
            useShellExecute = false;
            RedirectStandardOutput = true;
            RedirectStandardError = true;
            CreateNoWindow = true;
        }

        try
        {
            using (Process process = Process.Start(processInfo))
            {
                if (process == null)
                {
                    Console.WriteLine("Error: Process is null");
                    return;
                }

                // Read the output and errors
                string output = process.StandardOutput.ReadToEnd();
                string error = process.StandardError.ReadToEnd();

                process.WaitForExit();

                Console.WriteLine("Output: " + output);
                if (!string.IsNullOrEmpty(error))
                {
                    Console.WriteLine("Error: " + error);
                }
                else
                {
                    Console.WriteLine("Batch file executed successfully.");
                }
            }
        }
        catch(Exception e)
        {
            Console.WriteLine($"Exception: {e.Message}");
        }
    }
}

/* ================= DDS CONFIG ================= */
<qos_library name="QosLibrary">
    <qos_profile name="DefaultProfile">
        <participant_qos>
            <property>
                <value>
                    <element>
                        <name>dds.clock.internal_clock</name>
                        <value>monotonic,realtime</value>
                    </element>
                </value>
            </property>
        </participant_qos>

        <datawriter_qos>
            <reliability>
                <kind>RELIABLE_RELIABILITY_QOS</kind>
            </reliability>
            <history>
                <kind>KEEP_LAST_HISTORY_QOS</kind>
                <depth>1</depth>
            </history>
            <durability>
                <kind>TRANSIENT_LOCAL_DURABILITY_QOS</kind>
            </durability>
            <resource_limits>
                <initial_samples>1</initial_samples>
            </resource_limits>

            <property>
                <value>
                    <element>
                        <name>dds.data_writer.history.memory.fast_pool.pool_buffer_max_size</name>
                        <value> 32768</value>
                    </element>
                </value>
            </property>
        </datawriter_qos>
    </qos_profile>

    <qos_profile name="UDPv4Profile" base_name="DefaultProfile">
        <participant_qos>
            <transport_builtin>
                <mask>UDPv4</mask>
            </transport_builtin>
            <resource_limits>
                <type_code_max_serialized_length>0</type_code_max_serialized_length>
                <type_object_max_serialized_length>0</type_object_max_serialized_length>
                <participant_property_list_max_length>64</participant_property_list_max_length>
                <participant_property_string_max_length>2048</participant_property_string_max_length>
            </resource_limits>