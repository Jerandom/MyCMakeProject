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
    public event Action<T> onDataRecieved;

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

    public override void on_requested_deadline_missed(
        DDS.DataReader reader,
        ref DDS.RequestedDeadlineMissedStatus status)
    { }

    public override void on_requested_incompatible_qos(
        DDS.DataReader reader,
        DDS.RequestedIncompatibleQosStatus status)
    { }

    public override void on_sample_rejected(
        DDS.DataReader reader,
        ref DDS.SampleRejectedStatus status)
    { }

    public override void on_liveliness_changed(
        DDS.DataReader reader,
        ref DDS.LivelinessChangedStatus status)
    { }

    public override void on_sameple_lost(
        DDS.DataReader reader,
        ref DDS.SampleLostStatus status)
    { }

    public override void on_subscription_match(
        DDS.DataReader reader,
        ref DDS.SubscriptionMatchStatus status)
    { }

    public override void on_data_available(DDS.DataReader reader)
    {
        int counter = 1;
        object T_reader = null;

        // check if the event is registered, delay the code execution if no event is registered
        while(onDataRecieved == null && counter <= 5)
        {
            Console.Writeline($"No Subscribers for {typeof(T).FullName}, Delaying DataReader...{counter}s");
            Thread.Sleep(1000);
            counter++;
        }

        if(onDataRecieved == null)
        {
            Console.Writeline($"Still no subscribers for {typeof(T).FullName}");
            return;
        }

        // take data for reading
        try
        {
            // get and convert the object
            T_reader = DDSState.Instance.ddsDataReader[$"{typeof(T).FullName}"];

            // get the take() method
            MethodInfo takeMethod = T_reader.GetType.GetMethod("take", BindingFlags.Instance | BindingFlags.Public);
            if(takeMethod == null)
            {
                Console.Writeline($"The Class {T_reader.GetType().Name} does not have a instance take() method");
                return;
            }

            // Invoke take()
            takeMethod.Invoke(T_reader, new object[] { data_seq,
                                                       info_seq,
                                                       DDS.ResourceLimitsQosPolicy.LENGTH_UNLIMITED,
                                                       (uint)DDS.SampleStateKind.ANY_SAMPLE_STATE,
                                                       (uint)DDS.ViewStateKind.ANY_VIEW_STATE,
                                                       (uint)DDS.InstanceStateKind.ANY_INSTANCE_STATE });
        }
        catch (DDS.Retcode_NoData)
        {
            Console.Writeline($"NoData exception on DDS recieve for {typeof(T).FullName}");
            return;
        }
        catch (DDS.Exception)
        {
            Console.Writeline($"Error on take data in {typeof(T).FullName}");
            return;
        }
    }
}