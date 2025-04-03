public class DDSUtils
{
    public DDSUtils(int domainId,
                    string ddsQosFile,
                    string ddsQosLibrary,
                    string ddsQosProfile,
                    bool createSubscriber,
                    bool createPublisher)
    {
        // initialise states
        DDSState.Instance.ddsQosFile = ddsQosFile;
        DDSState.Instance.ddsQosLibrary = ddsQosLibrary;
        DDSState.Instance.ddsQosProfile = ddsQosProfile;
        
        // initialise nested dictionary
        DDSState.Instance.ddsTopic[domainId] = new Dictionary<string, Topic>();
        DDSState.Instance.ddsParticipants[domainId] = new Dictionary<string, DomainParticipant>();
        DDSState.Instance.ddsSubscriber[domainId] = new Dictionary<string, Subscriber>();
        DDSState.Instance.ddsPublisher[domainId] = new Dictionary<string, Publisher>();

        try
        {
            // initialise only once
            if(DDSState.Instance.ddsFactory == null)
            {
                // get instance of DomainParticipantFactory
                DDSState.Instance.ddsFactory = DDS.DomainParticipantFactory.get_instance();

                // initialise DDS Custom Qos
                DDS.DomainParticipantFactoryQos factoryQos = new DDS.DomainParticipantFactoryQos();
                DDSState.Instance.ddsFactory.get_qos(factoryQos);
                factoryQos.profile.url_profile.ensure_length(1, 1);
                factoryQos.profile.url_profile.from_array(new string[] { DDSState.Instance.ddsQosFile });
                DDSState.Instance.ddsFactory.set_qos(factoryQos);

                // creating participants
                DDSState.Instance.ddsParticipantQos = new DDS.DomainParticipantQos();
            }
        }
        catch(DDS.Exception e)
        {
            Console.Writeline($"[DDSHelper] Error when creating factory: " + e);
        }

        // setup Subscriber
        if(createSubscriber)
        {
            if(!SetupSubscriber(DDSState.Instance.ddsParticipants[domainId][ddsQosProfile], domainId))
            {
                return;
            }
        }

        // setup Publisher
        if(createPublisher)
        {
            if(!SetupPublisher(DDSState.Instance.ddsParticipants[domainId][ddsQosProfile], domainId))
            {
                return;
            }
        }
    }
}