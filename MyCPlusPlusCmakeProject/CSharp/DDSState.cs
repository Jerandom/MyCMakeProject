public class DDSState
{
    // Singleton instance
    private static readonly Lazy<DDSState> _instance = new Lazy<DDSState>(() => new DDSState());

    public static DDSState _instance
    {
        get { return _instance.Value; }
    }

    public DDS.DomainParticipantFactory ddsFactory;

    public string ddsQosFile;       // QOS File Location
    public string ddsQosLibrary;    // QOS Library
    public string ddsQosProfile;    // QOS Profile

    public DDS.DomainParticipantQos ddsParticipantQos;

    public Dictionary<int, Dictionary<string, DDS.Topic>> ddsTopic = new Dictionary<int, Dictionary<string, DDS.Topic>>();
    public Dictionary<int, Dictionary<string, DDS.DomainParticipant>> ddsParticipants = new Dictionary<int, Dictionary<string, DDS.DomainParticipant>>();
    public Dictionary<int, Dictionary<string, DDS.Subscriber>> ddsSubscriber = new Dictionary<int, Dictionary<string, DDS.Subscriber>>();
    public Dictionary<int, Dictionary<string, DDS.Publisher>> ddsPublisher = new Dictionary<int, Dictionary<string, DDS.Publisher>>();
    public Dictionary<string, DDS.DataReader> ddsDataReader = new Dictionary<string, DDS.DataReader>();
    public Dictionary<string, DDS.DataWriter> ddsDataWriter = new Dictionary<string, DDS.DataWriter>();
}