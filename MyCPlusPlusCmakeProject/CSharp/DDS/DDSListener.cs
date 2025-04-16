public class DDSListener<T> : DDS.DataReaderListener
{
    // Singleton Instance
    private static readonly Dictionary<Type, object> _instance = new Dictionary<Type, object>();

    public static DDSListener<T> Instance()
    {
        Type type = typeof(T);
        if(!_instance.ContainsKey(type))
        {
            _instance[type] = new DDSListener<T>();
        }
        return (DDSListener<T>)_instance[type];
    }

    // Event
    public event Action<T> onDataRecievedl

    private object data_seq;
    private DDS.SampleInfoSeq info_seq;

    protected DDSListener()
    {
        // construct Seq class name dynamically
        string className = $"{typeof(T).FullName}Seq";
        Assembly assembly = typeof(T).Assembly;

        // get type object for the generated Seq class
        Type newClassName = assembly.GetType(className);
        if(newClassName == null)
        {
            Console.Writeline($"The new class {newClassName} is not found in DDS Listener");
            return;
        }

        // assign instance of data_seq & info_seq
        data_seq = Activator.CreateInstance(newClassName);
        info_seq = new DDS.SampleInfoSeq();

        // Assign the DDS DataReader on a seperate thread, this is to avoid dead lock issue
        Task.Run(() => 
        {
            // assign DDS Reader to this object
            DDSState.Instance.ddsDataReader[$"{typeof(T).FullName}"].set_listener(this, DDS.StatusMask.STATUS_MASK_ALL);
        });
    }
}