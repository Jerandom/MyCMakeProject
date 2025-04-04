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

        // Setup Participants
        if(!SetupParticipants(domainId))
        {
            return;
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

    private DDS.DomainParticipant CreateParticipant(DomainParticipantFactory factory,
                                                    DomainParticipantQos partiQos,
                                                    string library,
                                                    string profile,
                                                    int ddsDomainId)
    {
        try
        {
            factory.get_participant_qos_from_profile(partiQos,
                                                    library,
                                                    profile);
            
            partiQos.participant_name.name = string.Format("{0}[{1}]",
                                                            "participant",
                                                            profile);

            return factory.create_participant(ddsDomainId,
                                                partiQos,
                                                null,
                                                DDS.StatusMask.STATUS_MASK_NONE);
        }
        catch (DDS.Exception e)
        {
            Console.Writeline("Unable to create participant, DDS Exception:" + e)
            return null;
        }
    }

    private bool SetupParticipants(int domainId)
    {
        // create participant & add them to the dictionary
        DDSState.Instance.ddsParticipants[domainId][DDSState.Instance.ddsQosProfile] = CreateParticipant(
            DDSState.Instance.ddsFactory,
            DDSState.Instance.ddsParticipantQos,
            DDSState.Instance.ddsQosLibrary,
            DDSState.Instance.ddsQosProfile,
            domainId
        );

        if(DDSState.Instance.ddsParticipants[domainId][DDSState.Instance.ddsQosProfile] == null)
        {
            // remove the null participant object
            DDSState.Instance.ddsParticipants.Remove(domainId);
            
            Console.Writeline($"[DDSHelper] Error when creating {DDSState.Instance.ddsQosProfile} participant");
            return false
        }

        return true;
    }

    private bool SetupSubscriber(DDS.DomainParticipant domainParticipant, int domainId)
    {
        //create Subscriber & add them to the list
        DDSState.Instance.ddsSubscriber[domainId][DDSState.Instance.ddsQosProfile] = domainParticipant.create_subscriber_with_profile(
            DDSState.Instance.ddsQosLibrary,
            DDSState.Instance.ddsQosProfile,
            null,
            DDS.StatusMask.STATUS_MASK_NONE
        );

        if(DDSState.Instance.ddsSubscriber[domainId][DDSState.Instance.ddsQosProfile] == null)
        {
            Console.Writeline($"[DDSHelper] Error when creating {DDSState.Instance.ddsQosProfile} Subscriber");
            return false;
        }

        return true;
    }

    private bool SetupPublisher(DDS.DomainParticipant domainParticipant, int domainId)
    {
        // create Publisher & add them to the list
        DDSState.Instance.ddsPublisher[domainId][DDSState.Instance.ddsQosProfile] = domainParticipant.create_publisher_with_profile(
            DDSState.Instance.ddsQosLibrary,
            DDSState.Instance.ddsQosProfile,
            null,
            DDS.StatusMask.STATUS_MASK_NONE
        );

        if(DDSState.Instance.ddsPublisher[domainId][DDSState.Instance.ddsQosProfile] == null)
        {
            Console.Writeline($"[DDSHelper] Error when creating {DDSState.Instance.ddsQosProfile} publisher");
            return false;
        }

        return true;
    }

    static public void CreateTopic<T>(DDS.DomainParticipant participant
                                      int domainId,
                                      string QosLibrary,
                                      string QosProfile,
                                      bool createDataReader,
                                      bool createDataWriter)
        where T : class
    {
        // construct TypeSupport class name dynamically
        string className = $"{typeof(T).FullName}TypeSupport";
        Assembly assembly = typeof(T).Assembly;

        // get type object for the generated TypeSupport class
        Type newClassName = assembly.GetType(className);
        if(newClassName == null)
        {
            Console.Writeline($"New class {newClassName} is not found in Create Topic");
            return;
        }

        // get the static get_type_name() method
        MethodInfo getTypeNameMethod = newClassName.GetMethod("get_type_name", BindingFlags.Static | BindingFlags.Public);
        if(getTypeNameMethod == null)
        {
            Console.Writeline($"Class {newClassName.Name} does not have a static get_type_name method");
            return;
        }

        // Invoke get_type_name() statically to get the type name
        string typeName = (string)getTypeNameMethod.Invoke(null, null);

        // get the register_type() method
        MethodInfo registerMethod = newClassName.GetMethod("register_type", BindingFlags.Static | BindingFlags.Public);
        if(registerMethod == null)
        {
            Console.Writeline($"Class {newClassName.Name} does not have a static register_type method");
            return;
        }

        // Invoke register_type(participant, typeName)
        registerMethod.Invoke(null, new object[] {participant, typeName});

        // create topic with profile
        DDSState.Instance.ddsTopic[domainId][$"{typeof(T).FullName}"] = participant.create_topic_with_profile(
            $"{typeof(T).FullName}",
            $"{typeof(T).FullName}",
            QosLibrary,
            QosProfile
            null
            DDS.StatusMask.STATUS_MASK_NONE
        );

        if(DDSState.Instance.ddsTopic[domainId][$"{typeof(T).FullName}"] == null)
        {
            Console.Writeline($"[DDSHelper] Failed to create {typeof(T).FullName} topic"); 
            return;   
        }

        // create data readers
        if(createDataReader)
        {
            //check if DDS is initialised
            if((DDSState.Instance == null) ||
               (!DDSState.Instance.ddsSubscriber.ContainsKey(domainId) &&
               !DDSState.Instance.ddsSubscriber[domainId].ContainsKey(QosProfile)))
            {
                Console.Writeline($"[DDSHelper] ddsSubscriber {QosProfile} not found");
                return;
            }
            else
            {
                // create Data Reader
                DDS.DataReader reader = DDSState.Instance.ddsSubscriber[domainId][QosProfile].create_datareader_with_profile(
                    DDSState.Instance.ddsTopic[domainId][typeof(T).FullName],
                    QosLibrary,
                    QosProfile,
                    null,
                    DDS.StatusMask.STATUS_MASK_NONE
                );

                if(reader == null)
                {
                    Console.Writeline($"[DDSHelper] Error creating data reader for {typeof(T).FullName}");
                    return;
                }

                // assign reader object if successful
                DDSState.Instance.ddsDataReader[$"{typeof(T).FullName}"] = reader;
                Console.Writeline($"[DDSHelper] Data reader for {typeof(T).FullName} initialised");
            }
        }

        // create data writers
        if(createDataWriter)
        {
            // check if DDS is initialised
            if((DDSState.Instance == null) ||
               (!DDSState.Instance.ddsPublisher.ContainsKey(domainId) &&
               !DDSState.Instance.ddsPublisher[domainId].ContainsKey(QosProfile)))
            {
                Console.Writeline($"[DDSHelper] ddsPublisher {QosProfile} not found");
                return;
            }
            else
            {
                // create Data Writer
                DDS.DataWriter writer = DDSState.Instance.ddsPublisher[domainId][QosProfile].create_datawriter_with_profile(
                    DDSState.Instance.ddsTopic[domainId][typeof(T).FullName],
                    QosLibrary,
                    QosProfile,
                    null,
                    DDS.StatusMask.STATUS_MASK_NONE
                );

                if(writer == null)
                {
                    Console.Writeline($"[DDSHelper] Error creating data writer for {typeof(T).FullName}");
                    return;
                }

                // assign writer object if successful
                DDSState.Instance.ddsDataWriter[$"{typeof(T).FullName}"] = writer;
                
            }
        }
    }
                                     
}