#include "epidemic-helper.h"
#include "epidemic-routing-protocol.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("EpidemicHelper");

EpidemicHelper::~EpidemicHelper ()
{
  NS_LOG_FUNCTION (this);
}

EpidemicHelper::EpidemicHelper () : Ipv4RoutingHelper ()
{
  NS_LOG_FUNCTION (this);
  m_agentFactory.SetTypeId ("ns3::Epidemic::RoutingProtocol");
}

EpidemicHelper* EpidemicHelper::Copy (void) const
{
  NS_LOG_FUNCTION (this);
  return new EpidemicHelper (*this);
}

Ptr<Ipv4RoutingProtocol> EpidemicHelper::Create (Ptr<Node> node) const
{
  NS_LOG_FUNCTION (this << node);
  Ptr<Epidemic::RoutingProtocol>
  agent = m_agentFactory.Create<Epidemic::RoutingProtocol> ();
  node->AggregateObject (agent);
  return agent;
}

void EpidemicHelper::Set (std::string name, const AttributeValue &value)
{
  NS_LOG_FUNCTION (this << name);
  m_agentFactory.Set (name, value);
}

} //end namespace ns3
