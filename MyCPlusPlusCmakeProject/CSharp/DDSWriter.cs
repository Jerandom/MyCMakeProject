public class DDSWriter<T>
{
    // Singleton Instance
    private static readonly Dictionary<Type, object> _instance = new Dictionary<Type, object>();

    public static DDSWriter<T> Instance()
    {
        Type type = typeof(T);
        if(!_instance.ContainsKey(type))
        {
            _instance[type] = new DDSWriter<T>();
        }
        return (DDSWriter<T>)_instance[type];
    }

    private object dataWriter;

    protected DDSWriter()
    {
        // get instance of the writer
        try
        {
            dataWriter = DDSState.Instance.ddsDataWriter[$"{typeof(T).FullName}"];
        }
        catch (Exception e)
        {
             Console.Writeline($"DDSWriter Exception: " + e);
        }
    }

    public void PublishDataWriter(T data)
    {
        // construct TypeSupport class name dynamically
        string className = $"{typeof(T).FullName}TypeSupport";
        Assembly assembly = typeof(T).Assembly;

        // get type object for the generated TypeSupport class
        Type newClassName = assembly.GetType(className);
        if(newClassName == null)
        {
            Console.Writeline($"The new class {newClassName} is not found in DDS Writer");
            return;
        }

        // get the create_data() method
        MethodInfo create_data = newClassName.GetMethod("create_data", BindingFlags.Static | BindingFlags.Public);
        if(create_data == null)
        {
            Console.Writeline($"The class {newClassName} does not have a Static create_data() method");
            return;
        }

        // invoke create_data()
        object instance = create_data.Invoke(null, null);
        if(instance == null)
        {
            Console.Writeline($"Error creating instance to publish {typeof(T).FullName}");
            return;
        }

        DDS.InstanceHanle_t instanceHandle = DDS.InstanceHanle_t.HANDLE_NIL;

        try
        {
            // set DataWriter values
            instance = data;

            // get the write() method
            MethodInfo write = dataWriter.GetType().GetMethod("write", BindingFlags.Instance | BindingFlags.Public);
            if(write == null)
            {
                Console.Writeline($"The class {dataWriter.GetType().Name} does not have a instance write() method");
                return;
            }

            // publish DataWriter
            write.Invoke(dataWriter, new object[] { instance, instanceHandle });
        }
        catch(DDS.Exception e)
        {
            Console.Writeline($"DDS Error in writing {typeof(T).FullName}: " + e);
        }
        catch(Exception e)
        {
            Console.Writeline($"Error in writing {typeof(T).FullName}: " + e);
        }
    }
}