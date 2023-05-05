#ifndef EPIDEMIC_HELPER_H
#define EPIDEMIC_HELPER_H

#include "ns3/object-factory.h"
#include "ns3/node.h"
#include "ns3/node-container.h"
#include "ns3/ipv4-routing-helper.h"


namespace ns3 {

class EpidemicHelper : public Ipv4RoutingHelper
{
public:
  /** Constructor */
  EpidemicHelper ();
  /** Destructor */
  ~EpidemicHelper ();
  // Inherited
  EpidemicHelper* Copy (void) const;
  virtual Ptr<Ipv4RoutingProtocol> Create (Ptr<Node> node) const;
  /**
   * Set attributes by name.
   * \param name the name of the attribute to set
   * \param value the value of the attribute to set.
   *
   * This method controls the attributes of "ns3::Epidemic::RoutingProtocol"
   */
  void Set (std::string name, const AttributeValue &value);

private:
  /** The factory to create Epidemic routing object */
  ObjectFactory m_agentFactory;
};

} //end namespace ns3

#endif /* EPIDEMIC_HELPER_H */
