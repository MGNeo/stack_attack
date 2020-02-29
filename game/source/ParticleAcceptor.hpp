#pragma once

namespace sa
{
  class ParticleVisitor;

  class ParticleAcceptor
  {
  public:

    using List = std::list<ParticleAcceptor>;

    virtual void accept(ParticleVisitor& _visitor) = 0;

  };
}
