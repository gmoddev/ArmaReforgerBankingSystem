// Not_Lowest
class TAG_PlayerCaps : EDF_DbEntity
{
    int m_iCapsBalance;

    static TAG_PlayerCaps Create(int initialBalance)
    {
        TAG_PlayerCaps instance();
        instance.m_iCapsBalance = initialBalance;
        return instance;
    }

    void AddCaps(int amount, IEntity pUserEntity)
    {
        m_iCapsBalance += amount;
        UpdateInventory(pUserEntity, amount);
    }

    void RemoveCaps(int amount, IEntity pUserEntity)
    {
        m_iCapsBalance -= amount;
        UpdateInventory(pUserEntity, -amount);
    }

    void UpdateInventory(IEntity pUserEntity, int amount)
    {
        if (amount > 0)
        {
            while (amount >= 100)
            {
                pUserEntity.GetInventory().AddItem("QuantumCaps");
                amount -= 100;
            }
            while (amount >= 10)
            {
                pUserEntity.GetInventory().AddItem("Caps_x10");
                amount -= 10;
            }
        }
        else
        {
            amount = -amount;
            while (amount >= 100)
            {
                IEntity quantumCapsItem = pUserEntity.GetInventory().FindItemByName("QuantumCaps");
                if (quantumCapsItem)
                {
                    pUserEntity.GetInventory().RemoveItem(quantumCapsItem);
                    amount -= 100;
                }
                else
                {
                    break;
                }
            }
            while (amount >= 10)
            {
                IEntity capsX10Item = pUserEntity.GetInventory().FindItemByName("Caps_x10");
                if (capsX10Item)
                {
                    pUserEntity.GetInventory().RemoveItem(capsX10Item);
                    amount -= 10;
                }
                else
                {
                    break;
                }
            }
        }
    }
};